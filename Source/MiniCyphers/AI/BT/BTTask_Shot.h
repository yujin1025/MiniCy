// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersTaskNode.h"
#include "BTTask_Shot.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTTask_Shot : public UMiniCyphersTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	float DetectRadius = 600.0f;
	
};
