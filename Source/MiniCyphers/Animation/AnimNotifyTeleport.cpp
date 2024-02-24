// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyTeleport.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyTeleport::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    IsFoundTarget = false;

    CurrentLocation = MyCharacter->GetActorLocation();
    TargetLocation = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_EngineTraceChannel1, 1000.0f, IsFoundTarget);

    FrameProgressingTime = 0.0f;

    DrawDebugSphere(GetWorld(), TargetLocation, 10.0f, 12, FColor::Green, false, 5.0f); //마우스 클릭한 곳 디버그
}

void UAnimNotifyTeleport::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    if (FrameProgressingTime >= MaxFrameProgressingTime)
        return;

    FrameProgressingTime += FrameDeltaTime * SpeedRate;

    auto LerpLocation = FMath::Lerp(CurrentLocation, TargetLocation, FrameProgressingTime);
    MyCharacter->SetActorLocation(LerpLocation);
}

void UAnimNotifyTeleport::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    if (!IsFoundTarget)
    {
        MyCharacter->StopAnimMontage();
    }
}
