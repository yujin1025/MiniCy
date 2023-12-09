// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MiniCyphersTaskNode.generated.h"

class UNavigationSystemV1;
class AMiniCyphersAIController;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class AAIController;
class AMiniCyphersCharacter;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	AMiniCyphersCharacter* GetCharacter(UBehaviorTreeComponent& OwnerComp);
	UNavigationSystemV1* GetNavigationSystem(UBehaviorTreeComponent& OwnerComp);
	AMiniCyphersAIController* GetAIController(UBehaviorTreeComponent& OwnerComp);
	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);
};
