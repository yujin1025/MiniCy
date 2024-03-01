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

	AMiniCyphersCharacter* DetectedTarget = nullptr;
	FindTarget(OwnerComp, MyCharacter, OUT DetectedTarget);
	
	SetDetectedTarget(OwnerComp, DetectedTarget);
	OnTickNode(OwnerComp, DeltaSeconds);
}

void UBTService_Detect::FindTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* MyCharacter, OUT AMiniCyphersCharacter* DetectedTarget)
{
	if (TryGetAttackerTrackingResult(OwnerComp, OUT DetectedTarget) == false)
	{
		TryGetOverlapTarget(MyCharacter, OUT DetectedTarget);
	}
}



bool UBTService_Detect::TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Owner->GetWorld();
	if (World == nullptr)
		return false;

	FVector Center = Owner->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Owner);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}
	
	return bResult;
}

bool UBTService_Detect::TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;

	if (TryGetOverlapResult(Owner, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			if (IsPlayerDetect && TargetCharacter->IsPlayer())
			{
				FoundTarget = TargetCharacter;
				break;
			}

			if (!IsPlayerDetect && TargetCharacter->IsPlayer() == false)
			{
				FoundTarget = TargetCharacter;
				break;
			}
		}
	}

	return FoundTarget != nullptr;
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

bool UBTService_Detect::TryGetAttackerTrackingResult(UBehaviorTreeComponent& OwnerComp, OUT AMiniCyphersCharacter*& FoundTarget)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return false;

	float RemainTrackingTime = BlackBoard->GetValueAsFloat(AMiniCyphersAIController::AttackerTrackingTimeKey);
	if (RemainTrackingTime > 0.01f)
	{
		auto* AttackerObject = BlackBoard->GetValueAsObject(AMiniCyphersAIController::AttackerObjectKey);
		if (AttackerObject != nullptr)
		{
			FoundTarget = Cast<AMiniCyphersCharacter>(AttackerObject);
		}
	}

	return FoundTarget != nullptr;
}

void UBTService_Detect::OnTickNode(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return;

	float CurrentRemainTime = BlackBoard->GetValueAsFloat(AMiniCyphersAIController::AttackerTrackingTimeKey);
	if (CurrentRemainTime < 0.01f)
		return;

	float RemainTime = CurrentRemainTime - DeltaSeconds;
	BlackBoard->SetValueAsFloat(AMiniCyphersAIController::AttackerTrackingTimeKey, RemainTime < 0.0f ? 0.0f : RemainTime);
}
