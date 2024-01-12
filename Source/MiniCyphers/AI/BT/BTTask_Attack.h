// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersTaskNode.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTTask_Attack : public UMiniCyphersTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void GetAttack(UBehaviorTreeComponent& OwnerComp);

private:
	UPROPERTY(EditAnywhere)
	EAttackType AttackType;

	bool bIsProcessing = false;
};
