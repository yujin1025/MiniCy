// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStiffCheckState.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/HitDeadComponent.h"

void UAnimNotifyStiffCheckState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	if (Character->RemainStiffTime > 0.01f)
	{
		Animation->RateScale = StiffAnimationSpeedRate;
	}
	else
	{
		Animation->RateScale = 1.0f;
	}
}

void UAnimNotifyStiffCheckState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Animation->RateScale = 1.0f;
}
