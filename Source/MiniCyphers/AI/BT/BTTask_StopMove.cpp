// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopMove.h"
#include "../MiniCyphersAIController.h"
#include "MiniCyphersTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_StopMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AIController->StopMovement();

	return EBTNodeResult::Succeeded;
}
