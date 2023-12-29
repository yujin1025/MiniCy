// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiva.h"
#include "Projectile/ShivaNormalAttackProjectile.h"
#include "Components/SceneComponent.h"


AShiva::AShiva()
{
	NormalAttackProjectileStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("NormalAttackProjectileStartLocation"));
	//NormalAttackProjectileStartLocation->SetupAttachment(FP_Gun);
	//NormalAttackProjectileStartLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	NormalAttackProjectileStartLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
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
	return true;
}

bool AShiva::IsSatisfiedGrabSkill()
{
	return true;
}

void AShiva::OnUseNormalAttack()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = ((NormalAttackProjectileStartLocation != nullptr) ? NormalAttackProjectileStartLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
			if (NormalAttackProjectileStartLocation == nullptr)
				return;
			const FVector SpawnLocation = NormalAttackProjectileStartLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			// spawn the projectile at the muzzle
			auto tempActor = World->SpawnActor<AShivaNormalAttackProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (tempActor == nullptr)
				return;
			tempActor->SetCharacterController(GetController());

		}
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
