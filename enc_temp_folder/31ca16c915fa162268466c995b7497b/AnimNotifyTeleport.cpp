// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyTeleport.h"
#include "../Character/MiniCyphersCharacter.h"

/*
void UAnimNotifyTeleport::Teleport(USkeletalMeshComponent* MeshComp)
{
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    AController* MyController = MyCharacter->GetController();
    if (!MyController)
        return;

    APlayerController* PlayerController = Cast<APlayerController>(MyController);
    if (!PlayerController)
        return;

    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    //if (HitResult.bBlockingHit)

    float TargetHeight = HitResult.ImpactPoint.Z;
    FVector NewLocation = FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, TargetHeight);

    MyCharacter->SetActorLocation(NewLocation);

    DrawDebugSphere(GetWorld(), NewLocation, 10.0f, 12, FColor::Green, false, 5.0f); //마우스 클릭한 곳 디버그

    ACharacter* HitCharacter = nullptr;
    const FVector TraceStart = MyCharacter->GetActorLocation();
    const FVector TraceEnd = NewLocation;
    FHitResult HitResultAfterTeleport;
    FCollisionQueryParams CollisionParams;

    // 레이 캐스트를 통해 순간이동 후 목표 지점에 적이 있는지 확인
    if (GetWorld()->LineTraceSingleByChannel(HitResultAfterTeleport, TraceStart, TraceEnd, ECC_Pawn, CollisionParams))
    {
        HitCharacter = Cast<ACharacter>(HitResultAfterTeleport.GetActor());

        if (HitCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("HitCharacter: %s"), *HitCharacter->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("HitCharacter is nullptr"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Hit"));
    }

    if (!HitCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("NoHit"));
        USkeletalMeshComponent* MyMesh = MyCharacter->GetMesh();

        if (MyMesh)
        {
            UAnimInstance* AnimInstance = MyMesh->GetAnimInstance();
            if (AnimInstance)
            {
                AnimInstance->Montage_Stop(0.0f);
                UE_LOG(LogTemp, Warning, TEXT("Stop"));
            }
        }
    }

    //현재 이동 안됨
}*/

void UAnimNotifyTeleport::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    
    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    FHitResult HitResult;
    FVector CurrentLocation = MyCharacter->GetActorLocation();
    FVector TargetLocation = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_Visibility, 1000.0f);

    TargetLocation = FMath::Lerp(CurrentLocation, TargetLocation, 0.7f);

    //float TargetHeight = HitResult.ImpactPoint.Z;
    //FVector NewLocation = FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, TargetHeight);

    MyCharacter->SetActorLocation(TargetLocation);

    DrawDebugSphere(GetWorld(), TargetLocation, 10.0f, 12, FColor::Green, false, 5.0f); //마우스 클릭한 곳 디버그

}

void UAnimNotifyTeleport::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UAnimNotifyTeleport::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    AController* MyController = MyCharacter->GetController();
    if (!MyController)
        return;

    APlayerController* PlayerController = Cast<APlayerController>(MyController);
    if (!PlayerController)
        return;

    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    float TargetHeight = HitResult.ImpactPoint.Z;
    FVector NewLocation = FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, TargetHeight);

    ACharacter* HitCharacter = nullptr;
    const FVector TraceStart = MyCharacter->GetActorLocation();
    const FVector TraceEnd = NewLocation;
    FHitResult HitResultAfterTeleport;
    FCollisionQueryParams CollisionParams;

    // 레이 캐스트를 통해 순간이동 후 목표 지점에 적이 있는지 확인
    if (GetWorld()->LineTraceSingleByChannel(HitResultAfterTeleport, TraceStart, TraceEnd, ECC_Pawn, CollisionParams))
    {
        HitCharacter = Cast<ACharacter>(HitResultAfterTeleport.GetActor());
    }

    if (!HitCharacter)
    {
        MyCharacter->StopAnimMontage(nullptr);
    }
}
