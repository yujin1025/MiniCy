// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersTaskNode.h"
#include "BTTask_RegistSummon.generated.h"

UENUM()
enum class EValueType
{
	INT = 0,
};

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTTask_RegistSummon : public UMiniCyphersTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
