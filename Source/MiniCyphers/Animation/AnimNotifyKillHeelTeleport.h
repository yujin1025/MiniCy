// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyMoveState.h"
#include "AnimNotifyKillHeelTeleport.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyKillHeelTeleport : public UAnimNotifyMoveState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void FindTarget(USkeletalMeshComponent* MeshComp) override;
private:
	bool IsFoundTarget = false;
};
