// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyEnd.generated.h"

class UComboActionComponent;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyEnd : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	TArray<UComboActionComponent*> GetComboComponents(USkeletalMeshComponent* MeshComp);

};
