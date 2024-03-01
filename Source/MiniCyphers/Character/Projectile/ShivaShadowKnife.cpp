// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaShadowKnife.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShivaShadowKnife::AShivaShadowKnife()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	CollisionComp->InitSphereRadius(AttackRange);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShivaShadowKnife::OnAttack);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp;
	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

	// Die after 1 seconds by default
	InitialLifeSpan = 3.0f;
}

void AShivaShadowKnife::BeginPlay()
{
	Super::BeginPlay();	
}

void AShivaShadowKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileMovementComp)
	{
		ProjectileMovementComp->Velocity = ProjectileDirection * ProjectileMovementComp->InitialSpeed;
	}
}

void AShivaShadowKnife::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ProjectileOwner == nullptr)
		return;
	
	AMiniCyphersCharacter* DamagedCharacter = Cast<AMiniCyphersCharacter>(OtherActor); //투사체에 맞은 놈
	if (DamagedCharacter->IsPlayer() == ProjectileOwner->IsPlayer())
		return;

	if ((OtherComp != nullptr) && DamagedCharacter != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent == nullptr)
				return;

			DamagedHealthComponent->ChangeHealth(ProjectileOwner, -10);
			Destroy();
		}
	}
}

void AShivaShadowKnife::Initialize(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character;
}

void AShivaShadowKnife::SetDirection(FVector Direction)
{
	ProjectileDirection = Direction;
}
