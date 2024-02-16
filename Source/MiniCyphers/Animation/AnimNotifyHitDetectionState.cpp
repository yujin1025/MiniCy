// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyHitDetectionState.h"
#include "../Character/HealthComponent.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../AI/BT/BTService_Detect.h"
#include "../AI/BT/MiniCyphersService.h"

UAnimNotifyHitDetectionState::UAnimNotifyHitDetectionState()
{
    bIsDouble = false;
}

void UAnimNotifyHitDetectionState::HitDetection(USkeletalMeshComponent* MeshComp)
{
	if (bHasTakenDamage)
		return;

	AMiniCyphersCharacter* TargetCharacter = nullptr;

	if (TryGetOverlapTarget(Cast<AMiniCyphersCharacter>(MeshComp->GetOwner()), TargetCharacter))
	{
		UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();

		if (DamagedHealthComponent)
		{
			int DamageAmount = bIsDouble ? 20 : 10;
			DamagedHealthComponent->ChangeHealth(TargetCharacter, -DamageAmount);
			bHasTakenDamage = true;
		}
	}
}

void UAnimNotifyHitDetectionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	bHasTakenDamage = false;
	HitDetection(MeshComp);
}

void UAnimNotifyHitDetectionState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	HitDetection(MeshComp);
}

void UAnimNotifyHitDetectionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	bHasTakenDamage = false;
}

AMiniCyphersCharacter* UAnimNotifyHitDetectionState::GetCharacter(const FOverlapResult& OverlapResult)
{
	auto* Actor = OverlapResult.GetActor();
	if (Actor == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Actor);
}

UHealthComponent* UAnimNotifyHitDetectionState::GetHealthComponent(USkeletalMeshComponent* MeshComp)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return nullptr;

	return owner->FindComponentByClass<UHealthComponent>();
}

bool UAnimNotifyHitDetectionState::TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Owner ? Owner->GetWorld() : nullptr;
	if (World == nullptr)
		return false;

	FVector Center = Owner->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Owner);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}

	return bResult;
}

bool UAnimNotifyHitDetectionState::TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Owner, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = UMiniCyphersService::GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			if (TargetCharacter->IsPlayer() == false)
				continue;

			bResult = true;
			FoundTarget = TargetCharacter;
			break;
		}
	}

	return bResult;
}

