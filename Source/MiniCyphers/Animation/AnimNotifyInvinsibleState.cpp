// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyInvinsibleState.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyInvinsibleState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	Character->bInvincible = true;
}

void UAnimNotifyInvinsibleState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{

}

void UAnimNotifyInvinsibleState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	Character->bInvincible = false;
}


