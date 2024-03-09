// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MiniCyphersAIController.h"

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return;
	
	AMiniCyphersCharacter* DetectedTarget = MyCharacter->GetTarget();
	SetDetectedTarget(OwnerComp, DetectedTarget);
	OnTickNode(OwnerComp, DeltaSeconds);
}

void UBTService_Detect::SetDetectedTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* TargetCharacter)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return;

	BlackBoard->SetValueAsObject(AMiniCyphersAIController::TargetObjectKey, TargetCharacter);

	if (TargetCharacter != nullptr)
	{
		BlackBoard->SetValueAsVector(AMiniCyphersAIController::PatrolPosKey, TargetCharacter->GetActorLocation());
	}
}

void UBTService_Detect::OnTickNode(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
	
}
