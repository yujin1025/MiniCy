// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MiniCyphersAIController.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMiniCyphersAIController();
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
	
};
