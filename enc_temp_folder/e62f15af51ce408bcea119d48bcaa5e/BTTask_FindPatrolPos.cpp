// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "MiniCyphersAIController.h"
#include "MiniCyphersTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto* NavSystem = GetNavigationSystem(OwnerComp);
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if(BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	FVector Origin = BlackBoard->GetValueAsVector(AMiniCyphersAIController::HomePosKey);

	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol) == false)
		return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(AMiniCyphersAIController::HomePosKey, NextPatrol.Location);
	return EBTNodeResult::Succeeded;
}
