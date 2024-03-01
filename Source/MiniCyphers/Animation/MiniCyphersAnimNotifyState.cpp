// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersAnimNotifyState.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/HealthComponent.h"

void UMiniCyphersAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	
}

void UMiniCyphersAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UMiniCyphersAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}

AMiniCyphersCharacter* UMiniCyphersAnimNotifyState::GetCharacter(const FOverlapResult& OverlapResult)
{
	auto* Actor = OverlapResult.GetActor();
	if (Actor == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Actor);
}

AMiniCyphersCharacter* UMiniCyphersAnimNotifyState::GetCharacter(USkeletalMeshComponent* MeshComp)
{
	return Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
}

UHealthComponent* UMiniCyphersAnimNotifyState::GetHealthComponent(USkeletalMeshComponent* MeshComp)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return nullptr;

	return owner->FindComponentByClass<UHealthComponent>();
}