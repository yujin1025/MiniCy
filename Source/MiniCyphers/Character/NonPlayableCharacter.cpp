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
AMiniCyphersCharacter* ANonPlayableCharacter::GetTarget()
{
	if (LastAttacker != nullptr)
		return LastAttacker;

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

