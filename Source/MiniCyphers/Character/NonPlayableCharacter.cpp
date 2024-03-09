// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"
#include "../AI/MiniCyphersAIController.h"
#include "../Character/Tower.h"

ANonPlayableCharacter::ANonPlayableCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

// 타워를 탐색해서 이동하는 로직
// 현재 센티넬, 투루퍼에서 사용 중
AMiniCyphersCharacter* ANonPlayableCharacter::GetTarget()
{
	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(this, OUT Targets) == false)
		return nullptr;

	for (auto& Target : Targets)
	{
		auto* Tower = Cast<ATower>(Target);
		if (Tower == nullptr)
			continue;

		return Tower;
	}

	return nullptr;
}

FVector ANonPlayableCharacter::GetTargetPosition()
{
	auto* Character = GetTarget();
	if (Character == nullptr)
		return FVector::ZeroVector;

	return Character->GetActorLocation();
}
