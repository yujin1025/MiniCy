// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBomb.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"

void ATowerBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentAttackCount > MaxAttackCount)
		return;

	if (ProjectileOwner == nullptr)
		return;

	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(ProjectileOwner, OUT Targets))
	{
		for (auto* Target : Targets)
		{
			UHealthComponent* DamagedHealthComponent = Target->FindComponentByClass<UHealthComponent>();

			if (DamagedHealthComponent)
			{
				DamagedHealthComponent->ChangeHealth(ProjectileOwner, DamageType, StiffTime, -DamageAmount, UpperVelocity, KnockBackDistance, IsMelee);
				CurrentAttackCount++;
			}
		}
	}
}
