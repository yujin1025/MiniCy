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
	virtual FVector FindTarget(USkeletalMeshComponent* MeshComp) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 3.0f;
};
