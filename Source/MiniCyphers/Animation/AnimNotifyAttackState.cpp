// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackState.h"
#include "../Character/HealthComponent.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../AI/BT/BTService_Detect.h"
#include "../AI/BT/MiniCyphersService.h"

UAnimNotifyAttackState::UAnimNotifyAttackState()
{
   
}

void UAnimNotifyAttackState::TryAttack(USkeletalMeshComponent* MeshComp)
{
	if (CurrentAttackCount >= MaxAttackCount)
		return;

	AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
	AMiniCyphersCharacter* TargetCharacter = nullptr;

	if (TryGetOverlapTarget(MyCharacter, TargetCharacter))
	{
		UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();

		if (DamagedHealthComponent)
		{
			DamagedHealthComponent->ChangeHealth(MyCharacter, -DamageAmount);
			CurrentAttackCount++;
		}
	}
}

void UAnimNotifyAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
}

FCollisionShape UAnimNotifyAttackState::MakeDetection(const float X, const float Y, const float Z)
{
	switch(DetectType)
	{
	case EDetectType::Square:
		return FCollisionShape::MakeBox(FVector(X, Y, Z));

	default:
		return FCollisionShape::MakeSphere(X);
	}
}

bool UAnimNotifyAttackState::TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults)
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
		MakeDetection(DetectX, DetectY, DetectZ),
		CollisionParam);

	DrawDebugSphere(World, Center, DetectX, 16, FColor::Red, false, 0.2f);
	return bResult;
}

bool UAnimNotifyAttackState::TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Owner, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
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
