// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyJumpState.h"
#include "../Character/MiniCyphersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyJumpState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	auto* Character = GetCharacter(MeshComp);
	if (Character == nullptr)
		return;

	Character->GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	Character->Jump();
}