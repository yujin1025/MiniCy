// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeShotComponent.h"
#include "Projectile/TowerShot.h"
#include "Projectile/StaticProjectile.h"
#include "Projectile/MiniCyphersProjectile.h"

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
    Super::OnAction();

    auto* TowerShot = Cast<ATowerShot>(GetOwner());
    if (TowerShot == nullptr)
        return;

    // 여기서 폭발 Projectile 생성합니다.
    auto* Bomb = GetWorld()->SpawnActor<AStaticProjectile>(ProjectileClass, TowerShot->GetActorLocation(), FRotator::ZeroRotator);
    if (Bomb == nullptr)
        return;

    Bomb->Initialize(TowerShot->ProjectileOwner);
    Bomb->SetDirection(TowerShot->ProjectileDirection);
}
