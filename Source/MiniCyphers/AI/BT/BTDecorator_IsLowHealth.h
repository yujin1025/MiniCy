// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersDecorator.h"
#include "BTDecorator_IsLowHealth.generated.h"

//class UHealthComponent;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTDecorator_IsLowHealth : public UMiniCyphersDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsLowHealth();

	protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere)
	int LowHealth;
};
