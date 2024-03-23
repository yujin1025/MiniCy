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
	TArray<AMiniCyphersCharacter*> TargetCharacters;

	if (TryGetOverlapTargets(MyCharacter, TargetCharacters))
	{
		for (auto* TargetCharacter : TargetCharacters)
		{
			int id = TargetCharacter->CharacterId;

			if (attackedCountsByCharacter.Contains(id) && attackedCountsByCharacter[id] > MaxAttackCountByEnemy)
				continue;

			if (attackedCountsByCharacter.Contains(id) == false)
			{
				attackedCountsByCharacter.Add(id, 1);
			}
			else
			{
				attackedCountsByCharacter[id]++;
			}

			UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent)
			{
				DamagedHealthComponent->ChangeHealth(MyCharacter, DamageType, StiffTime, -DamageAmount, UpperVelocity, KnockBackDistance, IsMelee);
				CurrentAttackCount++;
			}
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

FCollisionShape UAnimNotifyAttackState::MakeDetection(UWorld* World, FVector Center, FQuat Quat, const float X, const float Y, const float Z)
{
	switch(DetectType)
	{
	case EDetectType::Box:
		DrawDebugBox(World, Center + CenterOffset, FVector(X, Y, Z), Quat, FColor::Green, false, 0.2f);
		return FCollisionShape::MakeBox(FVector(X, Y, Z));

	default:
		DrawDebugSphere(World, Center + CenterOffset, DetectX, 16, FColor::Green, false, 0.2f);
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
		Center + CenterOffset,
		Owner->GetActorQuat(),
		ECollisionChannel::ECC_GameTraceChannel2,
		MakeDetection(World, Center, Owner->GetActorQuat(), DetectX, DetectY, DetectZ),
		CollisionParam);

	return bResult;
}

bool UAnimNotifyAttackState::TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			if (TargetCharacter->IsPlayerTeam == Character->IsPlayerTeam)
				continue;

			bResult = true;
			FoundTargets.Add(TargetCharacter);
			break;
		}
	}

	return bResult;
}
