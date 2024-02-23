// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyHit.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/HitDeadComponent.h"

void UAnimNotifyHit::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto HitDeadComponent = owner->FindComponentByClass<UHitDeadComponent>();
	if (HitDeadComponent == nullptr)
		return;

	HitDeadComponent->bHit = true;
}

void UAnimNotifyHit::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{

}

void UAnimNotifyHit::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto HitDeadComponent = owner->FindComponentByClass<UHitDeadComponent>();
	if (HitDeadComponent == nullptr)
		return;

	HitDeadComponent->bHit = false;
}

