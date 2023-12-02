// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AMiniCyphersAIController::AMiniCyphersAIController()
{
	
}

void AMiniCyphersAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* blackboardComponent = Blackboard;

	if (UseBlackboard(BBAsset, blackboardComponent))
	{
		RunBehaviorTree(BTAsset);
	}

}

void AMiniCyphersAIController::OnUnPossess()
{
	Super::OnUnPossess();
}