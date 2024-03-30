// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"
#include "../AI/MiniCyphersAIController.h"
#include "../Character/Tower.h"

ANonPlayableCharacter::ANonPlayableCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}


// 1. 최근에 나를 공격한 녀석이 있다면 그 녀석
// 2. 아니라면 타워
void ANonPlayableCharacter::UpdateTarget()
{
	if (LastAttacker != nullptr)
	{
		DetectedTarget = LastAttacker;
		return;
	}

	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(this, OUT Targets) == false)
		return;

	for (auto& Target : Targets)
	{
		auto* Tower = Cast<ATower>(Target);
		if (Tower == nullptr)
			continue;

		DetectedTarget = Tower;
	}
}

FVector ANonPlayableCharacter::GetTargetPosition()
{
	if (DetectedTarget == nullptr)
		return FVector::ZeroVector;

	return DetectedTarget->GetActorLocation();
}

void ANonPlayableCharacter::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	Super::OnHit(Attacker, DamageType, StiffTime, HealthAmount, UpperVelocity, KnockBackDistance, isMelee);

	LastAttacker = Attacker;
	LastAttackDeltaTime = 0.0f;
}

void ANonPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LastAttackTrackingValidTime < LastAttackDeltaTime)
	{
		LastAttacker = nullptr;
		LastAttackDeltaTime = 0.0f;
	}
	else
	{
		LastAttackDeltaTime += DeltaTime;
	}
}

