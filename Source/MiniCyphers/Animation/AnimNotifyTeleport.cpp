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
    
    auto AttackTargetLocation = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_GameTraceChannel2, TeleportDistance, IsFoundTarget);
    if (IsFoundTarget)
    {
        TargetLocation = FVector(AttackTargetLocation.X, AttackTargetLocation.Y, CurrentLocation.Z);;
    }
    else
    {
        bool NoUseFoundTarget = false;
        auto Location = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_WorldStatic, TeleportDistance, NoUseFoundTarget);
        TargetLocation = FVector(Location.X, Location.Y, CurrentLocation.Z);
    }

    FrameProgressingTime = 0.0f;
    Animation->RateScale = TeleportAnimationSpeedRate;
}

void UAnimNotifyTeleport::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    if (FrameProgressingTime >= 0.8f)
        return;

    FrameProgressingTime += FrameDeltaTime;

    auto LerpLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, FrameProgressingTime, SpeedRate);
    MyCharacter->SetActorLocation(LerpLocation);
}

void UAnimNotifyTeleport::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Animation->RateScale = 1.0f;
    
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    if (!IsFoundTarget)
    {
        MyCharacter->StopAnimMontage();
    }
}
