// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyMoveState.h"
#include "AnimNotifyChaseAttackState.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyChaseAttackState : public UAnimNotifyMoveState
{
	GENERATED_BODY()

protected:
	virtual void FindTarget(USkeletalMeshComponent* MeshComp) override;
	
};
