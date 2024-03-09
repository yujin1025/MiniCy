// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
        return EBTNodeResult::Failed;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return;

	auto* OtherCharacter = MyCharacter->GetTarget();
	if (OtherCharacter == nullptr)
		return;

	FVector CurrentLocation = MyCharacter->GetActorLocation();
	FVector TargetLocation = OtherCharacter->GetActorLocation();
	FVector TargetDirection = (TargetLocation - CurrentLocation).GetSafeNormal();

	MyCharacter->RotateToTarget(OtherCharacter, 5.0f);
	MyCharacter->Move(FVector2D(0, 1000));
}