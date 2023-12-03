// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Tara.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ATara : public APlayableCharacter
{
	GENERATED_BODY()

protected:
	virtual bool IsSatisfiedNormalAttack() override;
	virtual bool IsSatisfiedRightClickAttack() override;
	virtual bool IsSatisfiedShiftAttack() override;
	virtual bool IsSatisfiedQSkill() override;
	virtual bool IsSatisfiedUltimateSkill() override;
	virtual bool IsSatisfiedGrabSkill() override;

	virtual void OnUseNormalAttack() override;
	virtual void OnUseRightClickAttack() override;
	virtual void OnUseShiftLeftClickAttack() override;
	virtual void OnUseQSkill() override;
	virtual void OnUseUltimateSkill() override;
	virtual void OnUseGrabSkill() override;
	
};
