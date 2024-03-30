// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersCharacter.h"
#include "NonPlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ANonPlayableCharacter : public AMiniCyphersCharacter
{
	GENERATED_BODY()

public:
	ANonPlayableCharacter();
	
public:
	virtual void UpdateTarget() override;
	virtual FVector GetTargetPosition() override;

protected:
	AMiniCyphersCharacter* LastAttacker = nullptr;

	float LastAttackDeltaTime = 0.0f;
	float LastAttackTrackingValidTime = 5.0f;

protected:
	virtual void OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee);
	virtual void Tick(float DeltaTime) override;
};
