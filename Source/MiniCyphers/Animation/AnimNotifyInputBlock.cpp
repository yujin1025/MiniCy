// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyInputBlock.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyInputBlock::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto OwnerCharacter = Cast<AMiniCyphersCharacter>(owner);
	if (OwnerCharacter == nullptr)
		return;

	OwnerCharacter->bCanAttack = false;


}

void UAnimNotifyInputBlock::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{

}

void UAnimNotifyInputBlock::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	auto OwnerCharacter = Cast<AMiniCyphersCharacter>(owner);
	if (OwnerCharacter == nullptr)
		return;

	OwnerCharacter->bCanAttack = true;
}

