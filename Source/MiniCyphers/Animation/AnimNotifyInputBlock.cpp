// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyInputBlock.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/InputBlockComponent.h"

void UAnimNotifyInputBlock::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto* InputBlockComp = owner->FindComponentByClass<UInputBlockComponent>();
	if (InputBlockComp == nullptr)
		return;

	InputBlockComp->bInputBlock = true;
}

void UAnimNotifyInputBlock::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{

}

void UAnimNotifyInputBlock::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto* InputBlockComp = owner->FindComponentByClass<UInputBlockComponent>();
	if (InputBlockComp == nullptr)
		return;

	InputBlockComp->bInputBlock = false;
}

