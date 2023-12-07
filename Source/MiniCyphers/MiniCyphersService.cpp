// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "MiniCyphersAIController.h"
#include "AIController.h"
#include "MiniCyphersCharacter.h"

AMiniCyphersCharacter* UMiniCyphersService::GetCharacter(UBehaviorTreeComponent& OwnerComp)
{
	auto* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Pawn);
}

UBlackboardComponent* UMiniCyphersService::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent();
}

AMiniCyphersCharacter* UMiniCyphersService::GetCharacter(const FOverlapResult& OverlapResult)
{
	auto* Actor = OverlapResult.GetActor();
	if (Actor == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Actor);
}
