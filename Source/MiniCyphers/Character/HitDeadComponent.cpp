// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDeadComponent.h"

void UHitDeadComponent::OnHit(EDamageType DamageType, float StiffTime)
{
	AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return;

	if (DamageType == EDamageType::Stand)
	{
		int32 MontageCount = StandHitMontages.Num();
		if (MontageCount <= 0)
			return;

		CurrentHitMontageIndex = (CurrentHitMontageIndex + 1) % MontageCount;
		Character->PlayAnimMontage(StandHitMontages[CurrentHitMontageIndex]);
	}
	else if (DamageType == EDamageType::Airborne)
	{
		Character->PlayAnimMontage(AirborneHitMontage);
	}
	else if (DamageType == EDamageType::PowerKnockBack)
	{
		Character->PlayAnimMontage(PowerKnockBackMontage);
	}
}

void UHitDeadComponent::OnDead()
{
	AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return;

	Character->PlayAnimMontage(DeadMontage);

	bDead = true;
}
