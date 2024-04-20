// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersDecorator.h"
#include "../../MiniCyphersGameMode.h"
#include "BTDecorator_CheckTargetType.generated.h"


/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTDecorator_CheckTargetType : public UMiniCyphersDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	bool Check(UObject* Target) const;

	UPROPERTY(EditAnywhere)
	ECharacterType CheckType;
};
