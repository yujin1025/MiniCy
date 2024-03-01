// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shot.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_Shot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	auto* Target = BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey);
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	auto* TargetCharacter = Cast<AMiniCyphersCharacter>(Target);
	if (TargetCharacter == nullptr)
		return EBTNodeResult::Failed;

	UWorld* World = GetWorld();
	if (World)
	{
		FVector TargetLocation = TargetCharacter->GetActorLocation();
		DrawDebugSphere(World, TargetLocation, 200.0f, 16, FColor::Red, false, 0.2f);
	}

	return EBTNodeResult::InProgress;
}

/*
void UBTTask_Shot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);



}*/
