// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiva.h"


bool AShiva::IsSatisfiedNormalAttack()
{
	return Super::IsSatisfiedNormalAttack();
}

bool AShiva::IsSatisfiedRightClickAttack()
{
	return Super::IsSatisfiedRightClickAttack();
}

bool AShiva::IsSatisfiedShiftAttack()
{
	return Super::IsSatisfiedShiftAttack();
}

bool AShiva::IsSatisfiedQSkill()
{
	return Super::IsSatisfiedQSkill();
}

bool AShiva::IsSatisfiedUltimateSkill()
{
	return true;
}

bool AShiva::IsSatisfiedGrabSkill()
{
	return true;
}

void AShiva::OnUseNormalAttack()
{
}

void AShiva::OnUseRightClickAttack()
{
}

void AShiva::OnUseShiftLeftClickAttack()
{
}

void AShiva::OnUseQSkill()
{
}

void AShiva::OnUseUltimateSkill()
{
}

void AShiva::OnUseGrabSkill()
{
}
