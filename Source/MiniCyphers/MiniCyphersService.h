// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MiniCyphersService.generated.h"

class AMiniCyphersCharacter;
class UBehaviorTreeComponent;
class AAIController;
class AMiniCyphersAIController;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersService : public UBTService
{
	GENERATED_BODY()
	
protected:
	AMiniCyphersCharacter* GetCharacter(UBehaviorTreeComponent& OwnerComp);
	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);
	AMiniCyphersCharacter* GetCharacter(const FOverlapResult& OverlapResult);
};
