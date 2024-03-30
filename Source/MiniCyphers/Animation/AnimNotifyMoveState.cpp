// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyMoveState.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyMoveState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    FrameProgressingTime = 0.0f;

    CurrentLocation = MeshComp->GetOwner()->GetActorLocation();
    TargetLocation = FindTarget(MeshComp);

    auto Distance = (TargetLocation - CurrentLocation).Size();
    TargetLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, Distance / MoveDistance, 1);

    Animation->RateScale = MoveDistance / Distance >= 1.0f ? 1.0f : MoveDistance / Distance;

    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (MyCharacter == nullptr)
        return;

    auto* Target = MyCharacter->DetectedTarget;
    if (Target == nullptr)
        return;

    MyCharacter->RotateToTarget(Target, 200.0f); // 충분히 높은 수
}

void UAnimNotifyMoveState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (FrameProgressingTime >= 0.8f)
        return;

    FrameProgressingTime += FrameDeltaTime;

    auto LerpLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, FrameProgressingTime, SpeedRate);
    MeshComp->GetOwner()->SetActorLocation(LerpLocation);
}

void UAnimNotifyMoveState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Animation->RateScale = 1.0f;
}

FVector UAnimNotifyMoveState::FindTarget(USkeletalMeshComponent* MeshComp)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (MyCharacter == nullptr)
        return FVector::ZeroVector;

    FVector OriginTargetLocation = MyCharacter->GetTargetPosition();

    auto Distance = (OriginTargetLocation - CurrentLocation).Size();
    return FMath::VInterpTo(CurrentLocation, OriginTargetLocation, Distance / MoveDistance * TeleportDistanceMaxPercent, 1);
}
