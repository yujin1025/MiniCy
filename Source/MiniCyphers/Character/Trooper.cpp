// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
#include "../AI/MiniCyphersAIController.h"
#include "PlayableCharacter.h"

ATrooper::ATrooper()
{
	// AIControllerClass = BP로 된 센티넬 AI Controller를 넣어줄 것
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATrooper::BeginPlay()
{
	Super::BeginPlay();

	bSuperArmor = true; // 투루퍼는 항시 슈퍼아머
	IsPlayerTeam = false; // 적 팀
}

void ATrooper::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	Super::OnHit(Attacker, DamageType, StiffTime, HealthAmount, UpperVelocity, KnockBackDistance, isMelee);

	if (Cast<APlayableCharacter>(Attacker) != nullptr)
	{
		LastAttacker = Attacker;
		LastAttackDeltaTime = 0.0f;
	}
}
