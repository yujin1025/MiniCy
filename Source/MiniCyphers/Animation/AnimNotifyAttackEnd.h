// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyComboEnd.h"
#include "../Character/MiniCyphersCharacter.h"
#include "AnimNotifyAttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyAttackEnd : public UAnimNotifyComboEnd
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere)
	EAttackType AttackType;
};
