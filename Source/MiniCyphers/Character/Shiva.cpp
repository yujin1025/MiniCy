// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiva.h"
#include "Projectile/ShivaShadowKnife.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "../MiniCyphersPlayerController.h"

AShiva::AShiva()
{
	NormalAttackProjectileStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("NormalAttackProjctileStartLocation"));
	NormalAttackProjectileStartLocation->SetupAttachment(GetRootComponent());
	NormalAttackProjectileStartLocation->SetRelativeLocation(FVector(10.0f, 48.4f, 10.0f));

	SkillRange = 200.0f;
}

bool AShiva::IsSatisfiedNormalAttack()
{
	return Super::IsSatisfiedNormalAttack();
}

bool AShiva::IsSatisfiedRightClickAttack()
{
	return Super::IsSatisfiedRightClickAttack();
}

bool AShiva::IsSatisfiedShiftAttack()
{
	return Super::IsSatisfiedShiftAttack();
}

bool AShiva::IsSatisfiedQSkill()
{
	return Super::IsSatisfiedQSkill();
}

bool AShiva::IsSatisfiedUltimateSkill()
{
	return Super::IsSatisfiedUltimateSkill();
}

bool AShiva::IsSatisfiedGrabSkill()
{
	return Super::IsSatisfiedGrabSkill();
}

void AShiva::OnUseNormalAttack()
{
	// try and fire a projectile
	if (ProjectileClass == nullptr)
		return;

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		const FVector SpawnLocation = NormalAttackProjectileStartLocation->GetComponentLocation();
		
		bool IsFoundTarget = false;
		FVector TargetPosition = GetTargetPosition(ECollisionChannel::ECC_EngineTraceChannel1, 3500.0f, IsFoundTarget);
		const FVector SpawnRotation = (TargetPosition - SpawnLocation).GetSafeNormal();

		FActorSpawnParameters ActorSpawnParams;
		auto* Projectile = World->SpawnActor<AShivaShadowKnife>(ProjectileClass, SpawnLocation, SpawnRotation.Rotation(), ActorSpawnParams);
		if (Projectile == nullptr)
			return;

		Projectile->Initialize(this);
		Projectile->SetDirection(SpawnRotation);
	}
}

void AShiva::OnUseRightClickAttack()
{

}

void AShiva::OnUseShiftLeftClickAttack()
{
	
}

void AShiva::OnUseQSkill()
{

}

void AShiva::OnUseUltimateSkill()
{
}

void AShiva::OnUseGrabSkill()
{
}

void AShiva::OnDie()
{
	Super::OnDie();
}
