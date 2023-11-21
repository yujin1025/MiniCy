// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyHitDetectionState.h"
#include "HealthComponent.h"

void UAnimNotifyHitDetectionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UAnimNotifyHitDetectionState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UAnimNotifyHitDetectionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}

UHealthComponent* UAnimNotifyHitDetectionState::GetHealthComponent(USkeletalMeshComponent* MeshComp)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return nullptr;

	return owner->FindComponentByClass<UHealthComponent>();
}
