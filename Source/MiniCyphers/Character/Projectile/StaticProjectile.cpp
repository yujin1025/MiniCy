// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticProjectile.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "../TimeActionComponent.h"


AStaticProjectile::AStaticProjectile()
{
	TimeActionComponent = CreateDefaultSubobject<UTimeActionComponent>(TEXT("TimeShotComponent"));
}

void AStaticProjectile::Tick(float DeltaTime)
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
