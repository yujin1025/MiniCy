// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MiniCyphersAIController.h"

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
        return EBTNodeResult::Failed;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey));
	if (TargetActor == nullptr)
		return EBTNodeResult::Failed;

    AIController->SetFocus(TargetActor);
    AIController->MoveToActor(TargetActor, AcceptanceRadius);


	return EBTNodeResult::Succeeded;
}
