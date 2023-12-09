// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MiniCyphersDecorator.generated.h"

class AMiniCyphersCharacter;
class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	AMiniCyphersCharacter* GetCharacter(UBehaviorTreeComponent& OwnerComp) const;
	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp) const;

};
