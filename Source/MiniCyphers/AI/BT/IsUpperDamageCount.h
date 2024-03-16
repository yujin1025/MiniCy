// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersDecorator.h"
#include "IsUpperDamageCount.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UIsUpperDamageCount : public UMiniCyphersDecorator
{
	GENERATED_BODY()
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
