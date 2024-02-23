// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyTeleport.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyTeleport : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void Teleport(USkeletalMeshComponent* MeshComp);

};
