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
		Character->PlayAnimMontage(StandHitMontages[CurrentAirborneHitMontageIndex]);
	}
	
}

void UHitDeadComponent::PlayDeadMontage()
{
	int32 MontageCount = DeadMontages.Num();
	if (MontageCount <= 0)
		return;

	AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
	if (Character == nullptr)
		return;

	CurrentDeadMontageIndex = (CurrentDeadMontageIndex + 1) % MontageCount;
	Character->PlayAnimMontage(DeadMontages[CurrentDeadMontageIndex]);
}
