// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UMiniCyphersTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CurrentDeltaTime = 0.0f;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UMiniCyphersTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	CurrentDeltaTime += DeltaSeconds;
}

AMiniCyphersCharacter* UMiniCyphersTaskNode::GetCharacter(UBehaviorTreeComponent& OwnerComp)
{
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Pawn);
}

UNavigationSystemV1* UMiniCyphersTaskNode::GetNavigationSystem(UBehaviorTreeComponent& OwnerComp)
{
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return nullptr;

	return UNavigationSystemV1::GetNavigationSystem(Pawn->GetWorld());
}

AMiniCyphersAIController* UMiniCyphersTaskNode::GetAIController(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AMiniCyphersAIController>(OwnerComp.GetAIOwner());
}

UBlackboardComponent* UMiniCyphersTaskNode::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent();
}