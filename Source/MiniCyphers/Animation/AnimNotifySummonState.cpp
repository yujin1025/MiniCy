// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifySummonState.h"
#include "../Character/Shiva.h"
#include "../Character/Projectile/ShivaShadowKnife.h"
#include "../Character/Trooper.h"
#include "../Character/BombSentinel.h"
#include "../Character/Projectile/StaticProjectile.h"

void UAnimNotifySummonState::SummonObject(AMiniCyphersCharacter* Character)
{
	if (ProjectileClass == nullptr)
		return;

	if (SummonType == ESummonType::None)
		return;

	switch (SummonType)
	{
	case ESummonType::ShivaKnife:
		SummonShivaKnife(Cast<AShiva>(Character));
		break;

	case ESummonType::TrooperStone:
		SummonTrooperStone(Cast<ATrooper>(Character));
		break;

	case ESummonType::BombSentinel:
		SummonBombSentinel(Cast<ATrooper>(Character));
		break;

	case ESummonType::BombSentinelBomb:
		SummonBombSentinelBomb(Cast<ABombSentinel>(Character));
		break;
	}
}

void UAnimNotifySummonState::SummonTrooperStone(ATrooper* TrooperCharacter)
{
	UWorld* const World = TrooperCharacter->GetWorld();
	if (World != nullptr)
	{
		FVector SpawnCenterLocation = TrooperCharacter->GetMyLocation();
		
		FVector Dir = (TrooperCharacter->GetTargetPosition() - SpawnCenterLocation);
		FVector SpawnRotation = Dir.GetSafeNormal();
		SpawnRotation = FVector(SpawnRotation.X, SpawnRotation.Y, 0);

		for (FVector OffsetVector : TrooperSummonOffsetArray)
		{
			const FVector SpawnLocation = SpawnCenterLocation + OffsetVector * SpawnRotation;

			FActorSpawnParameters ActorSpawnParams;
			auto* Projectile = World->SpawnActor<AStaticProjectile>(ProjectileClass, SpawnLocation, SpawnRotation.Rotation(), ActorSpawnParams);
			if (Projectile == nullptr)
				return;

			Projectile->Initialize(TrooperCharacter);
			Projectile->SetDirection(SpawnRotation);
		}
	}
}

void UAnimNotifySummonState::SummonShivaKnife(AShiva* ShivaCharacter)
{
	UWorld* const World = ShivaCharacter->GetWorld();
	if (World != nullptr)
	{
		const FVector SpawnLocation = ShivaCharacter->GetProjectileStartLocation();

		bool IsFoundTarget = false;
		FVector TargetPosition = ShivaCharacter->GetTargetPosition(ECollisionChannel::ECC_EngineTraceChannel1, 3500.0f, IsFoundTarget);
		const FVector SpawnRotation = (TargetPosition - SpawnLocation).GetSafeNormal();

		FActorSpawnParameters ActorSpawnParams;
		auto* Projectile = World->SpawnActor<AShivaShadowKnife>(ProjectileClass, SpawnLocation, SpawnRotation.Rotation(), ActorSpawnParams);
		if (Projectile == nullptr)
			return;

		Projectile->Initialize(ShivaCharacter);
		Projectile->SetDirection(SpawnRotation);
	}
}

void UAnimNotifySummonState::SummonBombSentinel(ATrooper* TrooperCharacter)
{
	UWorld* const World = TrooperCharacter->GetWorld();
	if (World != nullptr)
	{
		FVector SpawnCenterLocation = TrooperCharacter->GetMyLocation();

		FVector Dir = (TrooperCharacter->GetTargetPosition() - SpawnCenterLocation);
		FVector SpawnRotation = Dir.GetSafeNormal();
		SpawnRotation = FVector(SpawnRotation.X, SpawnRotation.Y, 0);

		for (FVector OffsetVector : TrooperSummonOffsetArray)
		{
			const FVector SpawnLocation = SpawnCenterLocation + OffsetVector * SpawnRotation;

			FActorSpawnParameters ActorSpawnParams;
			World->SpawnActor<ABombSentinel>(SummonCharacterClass, SpawnLocation, SpawnRotation.Rotation(), ActorSpawnParams);
		}
	}
}

void UAnimNotifySummonState::SummonBombSentinelBomb(ABombSentinel* BombSentinel)
{
	UWorld* const World = BombSentinel->GetWorld();
	if (World != nullptr)
	{
		const FVector SpawnLocation = BombSentinel->GetMyLocation();

		FActorSpawnParameters ActorSpawnParams;
		auto* Projectile = World->SpawnActor<AStaticProjectile>(ProjectileClass, SpawnLocation, BombSentinel->GetActorRotation(), ActorSpawnParams);
		if (Projectile == nullptr)
			return;

		Projectile->Initialize(BombSentinel);
	}
}



void UAnimNotifySummonState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	SummonObject(Character);
}
