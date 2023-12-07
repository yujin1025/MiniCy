// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMiniCyphersAIController::HomePosKey(TEXT("HomePos"));
const FName AMiniCyphersAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMiniCyphersAIController::TargetObjectKey(TEXT("TargetObject"));


AMiniCyphersAIController::AMiniCyphersAIController()
{
	
}

void AMiniCyphersAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* blackboardComponent = Blackboard;

	if (UseBlackboard(BBAsset, blackboardComponent))
	{
		blackboardComponent->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		RunBehaviorTree(BTAsset);
	}

}

void AMiniCyphersAIController::OnUnPossess()
{
	Super::OnUnPossess();
}