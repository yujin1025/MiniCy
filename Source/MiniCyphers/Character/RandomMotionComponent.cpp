// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMotionComponent.h"


void URandomMotionComponent::NormalRandomAttack()
{
	auto character = this->GetCyphersCharacter();
	if (character == nullptr)
		return;

	if (RandomMontages.Num() > 0)
	{
		if (RandomMontages[0] && RandomMontages[1])
		{
			character->PlayAnimMontage(bUseAnim ? RandomMontages[0] : RandomMontages[1]);
			bUseAnim = !bUseAnim;
		}
	}

}
