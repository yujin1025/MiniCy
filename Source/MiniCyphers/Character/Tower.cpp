// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
#include "../AI/MiniCyphersAIController.h"

ATower::ATower()
{
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATower::BeginPlay()
{
	// 타워는 항시 슈퍼아머
	bSuperArmor = true;
}

// 타워는 가장 가까운 적을 탐색한다.
AMiniCyphersCharacter* ATower::GetTarget()
{
	AMiniCyphersCharacter* Target;

	if (TryGetOverlapTarget(this, OUT Target) == false)
		return nullptr;

	return Target;
}