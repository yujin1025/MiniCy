// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsSummonableBombSentinel.h"
#include "../../MiniCyphersGameMode.h"
#include "../../MiniCyphersGameState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../AI/MiniCyphersAIController.h"

bool UBTDecorator_IsSummonableBombSentinel::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return false;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return false;

	int CurrentSummonCount = BlackBoard->GetValueAsInt(AMiniCyphersAIController::BombSentinelSummonCountKey);
	int CurrentSentinelDeadCount = GameMode->MyGameState->GetDeadSentinelCount();
	
	int SentinelValidDeadCount = CurrentSentinelDeadCount - (SummonableSentinelDeathCount * CurrentSummonCount);
	return SummonableSentinelDeathCount < SentinelValidDeadCount;
}
