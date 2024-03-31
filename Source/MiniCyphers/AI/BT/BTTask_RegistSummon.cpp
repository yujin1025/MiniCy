// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RegistSummon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../AI/MiniCyphersAIController.h"

EBTNodeResult::Type UBTTask_RegistSummon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	int CurrentSummonCount = BlackBoard->GetValueAsInt(AMiniCyphersAIController::BombSentinelSummonCountKey);
	BlackBoard->SetValueAsInt(AMiniCyphersAIController::BombSentinelSummonCountKey, CurrentSummonCount + 1);
	return EBTNodeResult::Succeeded;
}
