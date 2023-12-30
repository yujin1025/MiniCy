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
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Assets/AI/BB_MiniCyphers.BB_MiniCyphers"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Assets/AI/BT_MiniCyphers.BT_MiniCyphers"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

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