// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckTargetType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <MiniCyphers/AI/MiniCyphersAIController.h>
#include <MiniCyphers/Character/Tower.h>
#include <MiniCyphers/Character/Sentinel.h>
#include <MiniCyphers/Character/Trooper.h>
#include <MiniCyphers/Character/PlayableCharacter.h>

bool UBTDecorator_CheckTargetType::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return false;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return false;

	auto TargetObject = BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey);
	if (TargetObject == nullptr)
		return false;

	return Check(TargetObject);
}

bool UBTDecorator_CheckTargetType::Check(UObject* Target) const
{
	if (Cast<ATower>(Target) != nullptr)
	{
		return CheckType == ECharacterType::Tower;
	}
	else if (Cast<ASentinel>(Target) != nullptr)
	{
		return CheckType == ECharacterType::Sentinel;
	}
	else if (Cast<ATrooper>(Target) != nullptr)
	{
		return CheckType == ECharacterType::Trooper;
	}
	else if (Cast<APlayableCharacter>(Target) != nullptr)
	{
		return CheckType == ECharacterType::Shiva || CheckType == ECharacterType::Tara;
	}

	return false;
}
