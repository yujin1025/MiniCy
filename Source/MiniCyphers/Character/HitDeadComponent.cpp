// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDeadComponent.h"

void UHitDeadComponent::PlayHitMontage()
{
	if (HitMontages.Num() > 0)
	{
		if (GetOwner() && GetOwner()->IsA(AMiniCyphersCharacter::StaticClass()))
		{
			AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
			if (Character)
			{
				int32 MontageCount = HitMontages.Num();
				if (MontageCount > 0)
				{
					CurrentHitMontageIndex = (CurrentHitMontageIndex + 1) % MontageCount;
					Character->PlayAnimMontage(HitMontages[CurrentHitMontageIndex]);
				}
			}
		}
	}
}

void UHitDeadComponent::PlayDeadMontage()
{
	if (DeadMontages.Num() > 0)
	{
		if (GetOwner() && GetOwner()->IsA(AMiniCyphersCharacter::StaticClass()))
		{
			AMiniCyphersCharacter* Character = Cast<AMiniCyphersCharacter>(GetOwner());
			if (Character)
			{
				int32 MontageCount = DeadMontages.Num();
				if (MontageCount > 0)
				{
					CurrentDeadMontageIndex = (CurrentDeadMontageIndex + 1) % MontageCount;
					Character->PlayAnimMontage(DeadMontages[CurrentDeadMontageIndex]);
				}
			}
		}
	}
}
