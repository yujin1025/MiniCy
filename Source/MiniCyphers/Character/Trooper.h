// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Trooper.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ATrooper : public ANonPlayableCharacter
{
	GENERATED_BODY()

public:
	ATrooper();

public:
	AMiniCyphersCharacter* LastAttacker = nullptr;
	
	float LastAttackDeltaTime = 0.0f;
	float LastAttackTrackingValidTime = 5.0f;

	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget) override;

	virtual void OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee);
	virtual void Tick(float DeltaTime) override;
};
