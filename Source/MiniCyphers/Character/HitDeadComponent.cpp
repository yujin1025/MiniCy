// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDeadComponent.h"

void UHitDeadComponent::PlayHitMontage(EDamageType DamageType)
{
	if (DamageType == EDamageType::Stand)
	{
		int32 MontageCount = StandHitMontages.Num();
		if (MontageCount <= 0)
			return;

		AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
		if (Character == nullptr)
			return;

		CurrentHitMontageIndex = (CurrentHitMontageIndex + 1) % MontageCount;
		Character->PlayAnimMontage(StandHitMontages[CurrentHitMontageIndex]);
	}
	else if (DamageType == EDamageType::Airborne)
	{
		int32 MontageCount = AirborneHitMontages.Num();
		if (MontageCount <= 0)
			return;

		AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
		if (Character == nullptr)
			return;

		CurrentAirborneHitMontageIndex = (CurrentAirborneHitMontageIndex + 1) % MontageCount;
		Character->PlayAnimMontage(AirborneHitMontages[CurrentAirborneHitMontageIndex]);
	}
	else if (DamageType == EDamageType::PowerKnockBack)
	{
		int32 MontageCount = PowerKnockBackMontages.Num();
		if (MontageCount <= 0)
			return;

		AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
		if (Character == nullptr)
			return;

		CurrentPowerKnockBackMontageIndex = (CurrentPowerKnockBackMontageIndex + 1) % MontageCount;
		Character->PlayAnimMontage(PowerKnockBackMontages[CurrentPowerKnockBackMontageIndex]);
	}

	bHit = true;
}

void UHitDeadComponent::PlayDeadMontage()
{
	AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return;

	Character->PlayAnimMontage(DeadMontage);

	bDead = true;
}
