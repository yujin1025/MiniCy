// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Shiva.generated.h"

/**
 * 
 */

class USceneComponent;

UCLASS()
class MINICYPHERS_API AShiva : public APlayableCharacter
{
	GENERATED_BODY()

public:
	AShiva();

protected:
	virtual void OnUseNormalAttack() override;
	virtual void OnUseRightClickAttack() override;
	virtual void OnUseShiftLeftClickAttack() override;
	virtual void OnUseQSkill() override;
	virtual void OnUseUltimateSkill() override;
	virtual void OnUseGrabSkill() override;

	virtual void OnDie() override;


public:
	FVector GetProjectileStartLocation();

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USceneComponent* NormalAttackProjectileStartLocation;
};
