// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifySummonState.h"
#include "../Character/Shiva.h"
#include "../Character/Projectile/ShivaShadowKnife.h"

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

	case ESummonType::TowerShot:
		break;
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

void UAnimNotifySummonState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	SummonObject(Character);
}
