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

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return EBTNodeResult::Failed;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	auto* OtherCharacter = Cast<AMiniCyphersCharacter>(BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey));
	if (OtherCharacter == nullptr)
		return EBTNodeResult::Failed;

	MyCharacter->RotateToTarget(OtherCharacter, 5.0f);
	AIController->MoveToLocation(OtherCharacter->GetMyLocation(), 200.0f);

	return EBTNodeResult::Succeeded;
}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return;

	AIController->StopMovement();
}
