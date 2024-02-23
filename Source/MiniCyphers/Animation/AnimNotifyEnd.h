// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyEnd.generated.h"

class UComboActionComponent;
class AMiniCyphersCharacter;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyComboEnd : public UAnimNotify
{
	GENERATED_BODY()
	
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	TArray<UComboActionComponent*> GetComboComponents(USkeletalMeshComponent* MeshComp);

	AMiniCyphersCharacter* GetCharacter(USkeletalMeshComponent* MeshComp);
};
