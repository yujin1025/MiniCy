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

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* NormalTrooper;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* RightClickTrooper;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* QSkillTrooper;
	
	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* NormalAttackAnimA;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* NormalAttackAnimB;

	bool bUseAnimA = true;

	class UHealthComponent* HealthComponent;
	
public:
	ATrooper();

protected:
	virtual void OnUseNormalAttack() override;
	virtual void OnUseRightClickAttack() override;
	virtual void OnUseShiftLeftClickAttack() override;
	virtual void OnUseQSkill() override;
};
