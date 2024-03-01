// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTower.h"
#include "../../Character/Tower.h"

void UBTService_DetectTower::FindTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* MyCharacter, OUT AMiniCyphersCharacter*& DetectedTarget)
{
	TArray<AMiniCyphersCharacter*> FoundTargets;

	TryGetOverlapTargets(MyCharacter, OUT FoundTargets);

	for (auto Target : FoundTargets)
	{
		auto* Tower = Cast<ATower>(Target);
		if (Tower == nullptr)
			continue;

		DetectedTarget = Tower;
	}
}
