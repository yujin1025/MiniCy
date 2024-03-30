// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersTaskNode.h"
#include "BTTask_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTTask_MoveToTarget : public UMiniCyphersTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MoveToTarget();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
public:
	UPROPERTY(EditAnyWhere)
	float MoveSpeed = 1500.0f;
};
