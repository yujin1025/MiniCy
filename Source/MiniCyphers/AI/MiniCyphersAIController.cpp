// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/HealthComponent.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/MiniCyphersCharacter.h"

const FName AMiniCyphersAIController::HomePosKey(TEXT("HomePos"));
const FName AMiniCyphersAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMiniCyphersAIController::TargetObjectKey(TEXT("TargetObject"));
const FName AMiniCyphersAIController::DamagedCountKey(TEXT("DamagedCount"));
const FName AMiniCyphersAIController::DamagedTypeKey(TEXT("DamagedType"));


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

	auto* InChar = Cast<AMiniCyphersCharacter>(InPawn);
	if (InChar == nullptr)
		return;

	SetCharacterPerception(InChar);
}

void AMiniCyphersAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMiniCyphersAIController::SetCharacterPerception(AMiniCyphersCharacter* InChar)
{
	InChar->HealthComponent->OnDamaged.AddUObject(this, &AMiniCyphersAIController::OnDamaged);
}

void AMiniCyphersAIController::OnDamaged(AMiniCyphersCharacter* Attacker, float Amount, bool isMelee)
{
	UBlackboardComponent* blackboardComponent = Blackboard;
	if (blackboardComponent == nullptr)
		return;

	int DamagedCount = blackboardComponent->GetValueAsInt(DamagedCountKey);
	blackboardComponent->SetValueAsInt(DamagedCountKey, DamagedCount + 1);
	blackboardComponent->SetValueAsBool(DamagedTypeKey, isMelee);
}
