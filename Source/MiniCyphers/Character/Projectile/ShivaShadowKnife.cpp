// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaShadowKnife.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

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
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;
}

void AShivaShadowKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileMovementComp)
	{
		ProjectileMovementComp->Velocity = ProjectileDirection * ProjectileSpeed;
	}

	if (CurrentDeltaTime > LifeSeconds)
	{
		Destroy();
	}

	CurrentDeltaTime += DeltaTime;
}

void AShivaShadowKnife::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ProjectileOwner == nullptr)
		return;
	
	UWorld* const World = GetWorld();
	if (World == nullptr)
		return;

	if (OtherComp == nullptr)
		return;

	AMiniCyphersCharacter* DamagedCharacter = Cast<AMiniCyphersCharacter>(OtherActor); //투사체에 맞은 놈
	if (DamagedCharacter != nullptr && DamagedCharacter->IsPlayer() == ProjectileOwner->IsPlayer())
		return;

	const FVector SpawnLocation = Hit.ImpactPoint;
	FActorSpawnParameters ActorSpawnParams;
	UParticleSystemComponent* ParticleSystemComponent = nullptr;
	
	if (DamagedCharacter != nullptr)
	{
		UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
		if (DamagedHealthComponent == nullptr)
			return;

		DamagedHealthComponent->ChangeHealth(ProjectileOwner, EDamageType::Stand, -DamageAmount, 0, KnockBackDistance, false);

		if (EnemyHitParticleEffect)
		{
			ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnemyHitParticleEffect, SpawnLocation);
		}
	}
	else
	{
		if (WallHitParticleEffect)
		{
			ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WallHitParticleEffect, SpawnLocation);
		}
	}

	if (ParticleSystemComponent)
	{
		ParticleSystemComponent->SetRelativeScale3D(FVector(ParticleScale));
	}

	Destroy();
}

void AShivaShadowKnife::Initialize(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character;
}

void AShivaShadowKnife::SetDirection(FVector Direction)
{
	ProjectileDirection = Direction;
}
