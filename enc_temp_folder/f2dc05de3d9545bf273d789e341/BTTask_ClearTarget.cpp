// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearTarget.h"
#include "../MiniCyphersAIController.h"
#include "MiniCyphersTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_ClearTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(AMiniCyphersAIController::PatrolPosKey, FVector::ZeroVector);
	BlackBoard->SetValueAsObject(AMiniCyphersAIController::TargetObjectKey, nullptr);
	BlackBoard->SetValueAsObject(AMiniCyphersAIController::AttackerObjectKey, nullptr);
	BlackBoard->SetValueAsFloat(AMiniCyphersAIController::AttackerTrackingTimeKey, 0.0f);

	MyCharacter->GetCharacterMovement()->Velocity = FVector::ZeroVector;

	return EBTNodeResult::Succeeded;
}
