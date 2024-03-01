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

	virtual void OnDie() override;


public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AShivaShadowKnife> ProjectileClass;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USceneComponent* NormalAttackProjectileStartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector NormalAttackStartLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills")
	float SkillRange;

	bool bInvincible;
};
