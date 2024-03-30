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
	virtual void OnUseNormalAttack() override;
	virtual void OnUseRightClickAttack() override;
	virtual void OnUseShiftLeftClickAttack() override;
	virtual void OnUseQSkill() override;
	virtual void OnUseUltimateSkill() override;
	virtual void OnUseGrabSkill() override;
	
};
