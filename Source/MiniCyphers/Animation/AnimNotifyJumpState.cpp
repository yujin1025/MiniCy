// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyJumpState.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyJumpState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	Character->Jump();
}