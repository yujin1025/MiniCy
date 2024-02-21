// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaNormalAttackProjectile.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShivaNormalAttackProjectile::AShivaNormalAttackProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	CollisionComp->InitSphereRadius(AttackRange);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShivaNormalAttackProjectile::OnAttack);

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

void AShivaNormalAttackProjectile::BeginPlay()
{
	Super::BeginPlay();	
}

void AShivaNormalAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShivaNormalAttackProjectile::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMiniCyphersCharacter* DamagedCharacter = Cast<AMiniCyphersCharacter>(OtherActor); //투사체에 맞은 놈

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

void AShivaNormalAttackProjectile::Initialize(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character;

	FVector Direction = Character->GetActorRotation().Vector();
	// ProjectileMovementComp->Velocity = Direction * ProjectileMovementComp->InitialSpeed;
}
