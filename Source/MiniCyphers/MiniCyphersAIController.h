// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MiniCyphersAIController.generated.h"

/**
 * 블루 프린트로 파생 컨트롤러를 만듬
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
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset;
	
	UPROPERTY(EditAnywhere)
	class UBlackboardData* BBAsset;
};
