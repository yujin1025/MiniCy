// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyChaseAttackState.h"
#include "../Character/MiniCyphersCharacter.h"

FVector UAnimNotifyChaseAttackState::FindTarget(USkeletalMeshComponent* MeshComp)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (MyCharacter == nullptr)
        return FVector::ZeroVector;

    auto AttackTargetLocation = MyCharacter->GetTargetPosition();
    return FVector(AttackTargetLocation.X, AttackTargetLocation.Y, CurrentLocation.Z);
}

void UAnimNotifyChaseAttackState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (MyCharacter == nullptr)
        return;

    auto* Target = MyCharacter->GetTarget();
    MyCharacter->RotateToTarget(Target, RotationSpeed);
}