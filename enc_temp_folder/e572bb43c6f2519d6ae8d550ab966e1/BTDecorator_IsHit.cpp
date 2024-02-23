// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsHit.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "../../Character/HitDeadComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UBTDecorator_IsHit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return false;

	auto* HitDeadComponent = MyCharacter->FindComponentByClass<UHitDeadComponent>();
	if (HitDeadComponent == nullptr)
		return false;

	bool bHit = HitDeadComponent->bHit;
	return HitDeadComponent->bHit;
}
