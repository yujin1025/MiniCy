// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersDecorator.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "AIController.h"

AMiniCyphersCharacter* UMiniCyphersDecorator::GetCharacter(UBehaviorTreeComponent& OwnerComp) const
{
	auto* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Pawn);
}

UBlackboardComponent* UMiniCyphersDecorator::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent();
}
