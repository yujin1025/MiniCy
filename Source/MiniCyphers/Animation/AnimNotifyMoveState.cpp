// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyMoveState.h"

void UAnimNotifyMoveState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    FrameProgressingTime = 0.0f;
    CurrentLocation = MeshComp->GetOwner()->GetActorLocation();
}

void UAnimNotifyMoveState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (FrameProgressingTime >= 0.8f)
        return;

    FrameProgressingTime += FrameDeltaTime;

    TargetLocation = FindTarget(MeshComp);

    auto LerpLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, FrameProgressingTime, SpeedRate);
    MeshComp->GetOwner()->SetActorLocation(LerpLocation);
}

void UAnimNotifyMoveState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}

FVector UAnimNotifyMoveState::FindTarget(USkeletalMeshComponent* MeshComp)
{
    return FVector::ZeroVector;
}
