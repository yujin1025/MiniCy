// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../AI/MiniCyphersAIController.h"


ATrooper::ATrooper()
{
	// AIControllerClass = BP로 된 센티넬 AI Controller를 넣어줄 것
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATrooper::OnUseNormalAttack()
{
	Super::OnUseNormalAttack();

	if (NormalAttackAnimA && NormalAttackAnimB)
	{
		PlayAnimMontage(bUseAnimA ? NormalAttackAnimA : NormalAttackAnimB);
		bUseAnimA = !bUseAnimA;
	}

	if (NormalTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NormalTrooper, GetActorLocation());
	}
}

void ATrooper::OnUseRightClickAttack()
{
	Super::OnUseRightClickAttack();
	if (RightClickTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RightClickTrooper, GetActorLocation());
	}
}

void ATrooper::OnUseShiftLeftClickAttack()
{
	Super::OnUseShiftLeftClickAttack();

	HealthComponent = FindComponentByClass<UHealthComponent>();
	if (HealthComponent)
	{
		HealthComponent->ChangeHealth(-20, true); //이렇게하면 플레이어가아니라 몬스터가 깎임..
	}
}

void ATrooper::OnUseQSkill()
{
	Super::OnUseQSkill();
	if (QSkillTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, QSkillTrooper, GetActorLocation());
	}
}

