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

	AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
	AMiniCyphersCharacter* TargetCharacter = nullptr;

	if (TryGetOverlapTarget(MyCharacter, TargetCharacter))
	{
		UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();

		if (DamagedHealthComponent)
		{
			int DamageAmount = bIsDouble ? 20 : 10;
			DamagedHealthComponent->ChangeHealth(MyCharacter, -DamageAmount);
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

FCollisionShape UAnimNotifyHitDetectionState::MakeDetection(const float SphereRadius, const float Long)
{
	return FCollisionShape::MakeSphere(SphereRadius);
	//구형태나 캡슐형태를 하고싶으면 그 곳에서 이 함수를 오버라이드하기, 만약 캡슐이면 거기선 2개 받는 식으로
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
		MakeDetection(DetectShort, DetectLong),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, DetectShort, 16, FColor::Red, false, 0.2f);
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

			if (TargetCharacter->IsPlayer() == Owner->IsPlayer())
				continue;

			bResult = true;
			FoundTarget = TargetCharacter;
			break;
		}
	}

	return bResult;
}

