// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersService.h"
#include "BTService_DamagePerception.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTService_DamagePerception : public UMiniCyphersService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
