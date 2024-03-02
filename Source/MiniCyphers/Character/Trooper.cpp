// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
#include "../AI/MiniCyphersAIController.h"

ATrooper::ATrooper()
{
	// AIControllerClass = BP로 된 센티넬 AI Controller를 넣어줄 것
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

FVector ATrooper::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget)
{
	auto* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return FVector::Zero();

	if (LastAttacker != nullptr)
		return LastAttacker->GetActorLocation();

	return Super::GetTargetPosition(Channel, RayCastDistance, OUT IsFoundTarget);
}

void ATrooper::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	Super::OnHit(Attacker, DamageType, HealthAmount, UpperVelocity, KnockBackDistance, isMelee);
	
	LastAttacker = Attacker;
	LastAttackDeltaTime = 0.0f;
}

void ATrooper::Tick(float DeltaTime)
{
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
