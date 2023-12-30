// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaNormalAttackProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShivaNormalAttackProjectile::AShivaNormalAttackProjectile()
{

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AShivaNormalAttackProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp;
	ProjectileMovementComp->InitialSpeed = 2000.f;
	ProjectileMovementComp->MaxSpeed = 2000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

	// Die after 1 seconds by default
	InitialLifeSpan = 0.5f;

}

void AShivaNormalAttackProjectile::BeginPlay()
{
	
}

void AShivaNormalAttackProjectile::Tick(float DeltaTime)
{

}

// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
void AShivaNormalAttackProjectile::InitVelocity(const FVector& ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection * ProjectileMovementComp->InitialSpeed;
}


AController* AShivaNormalAttackProjectile::SetCharacterController(AController* Controller)
{
	CharacterController = Controller;
	return CharacterController;
}
