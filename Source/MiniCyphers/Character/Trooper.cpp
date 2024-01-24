// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
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

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		AMiniCyphersPlayerState* CharPlayerState = GameMode->MyPlayerState;
		if (CharPlayerState)
		{
			AMiniCyphersCharacter* PlayerCharacter = Cast<AMiniCyphersCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			if (PlayerCharacter)
			{
				HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
				if (HealthComponent)
				{
					HealthComponent->ChangeHealth(this, -10, true);
				}
			}
		}
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

