// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifyTeleport.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyTeleport : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	FVector CurrentLocation;
	FVector TargetLocation;
	bool IsFoundTarget = false;

	float FrameProgressingTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float TeleportDistance = 1000.0f;

	UPROPERTY(EditAnywhere)
	float TeleportDistanceMaxPercent = 0.8f;

	UPROPERTY(EditAnywhere)
	float TeleportAnimationSpeedRate = 0.2f;
	
	UPROPERTY(EditAnywhere)
	float SpeedRate = 3.0f;
};
