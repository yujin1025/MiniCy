// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"
#include "../AI/MiniCyphersAIController.h"
#include "../Character/Tower.h"
ANonPlayableCharacter::ANonPlayableCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

FVector ANonPlayableCharacter::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget)
{
	auto* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return FVector::Zero();

	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(Character, OUT Targets) == false)
		return FVector::Zero();

	for (auto& Target : Targets)
	{
		auto* Tower = Cast<ATower>(Target);
		if (Tower == nullptr)
			continue;

		return Tower->GetActorLocation();
	}
	return FVector();
}
