// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeShotComponent.h"
#include "Projectile/TowerShot.h"

void UTimeShotComponent::TryAction()
{
    AActor* OwnerActor = GetOwner();

    ATowerShot* TowerShot = Cast<ATowerShot>(OwnerActor);
    if (TowerShot)
    {
        UStaticMeshComponent* StaticMeshComponent = TowerShot->StaticMesh;
        /*
        UMaterialInstanceDynamic* MaterialInstance = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(0);

        if (MaterialInstance)
        {
            float CurrentOpacity;
            MaterialInstance->GetScalarParameterValue(TEXT("Alpha"), CurrentOpacity);

            CurrentOpacity -= 0.2f;
            CurrentOpacity = FMath::Max(CurrentOpacity, 0.0f);

            MaterialInstance->SetScalarParameterValue(TEXT("Alpha"), CurrentOpacity);
        }*/
    }
}

void UTimeShotComponent::OnAction()
{
}
