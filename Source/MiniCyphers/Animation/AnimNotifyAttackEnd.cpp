// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackEnd.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/ComboActionComponent.h"

void UAnimNotifyAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	auto* Character = GetCharacter(MeshComp);
	if (Character != nullptr)
	{
		Character->OnFinishedSkillMotion(AttackType);
	}
}
