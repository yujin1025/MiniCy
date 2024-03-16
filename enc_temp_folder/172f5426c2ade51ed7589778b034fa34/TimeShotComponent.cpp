// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeShotComponent.h"
#include "Projectile/TowerShot.h"

void UTimeShotComponent::StartAction()
{
    ATowerShot* TowerShot = Cast<ATowerShot>(GetOwner());
    if (TowerShot != nullptr)
    {
        TowerShot->SetAlpha(1.0f);
    }
}

void UTimeShotComponent::UpdateAction(float DeltaTime)
{
    ATowerShot* TowerShot = Cast<ATowerShot>(GetOwner());
    if (TowerShot != nullptr)
    {
        TowerShot->ChangeAlpha(-1 * DeltaTime / ReserveTime);
    }

}

void UTimeShotComponent::OnAction()
{
    ATowerShot* TowerShot = Cast<ATowerShot>(GetOwner());
    if (TowerShot != nullptr)
    {
        TowerShot->SetAlpha(0.0f);
    }
}
