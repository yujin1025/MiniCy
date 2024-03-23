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
	
	TowerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerMesh");
	TowerStaticMesh->SetupAttachment(RootComponent);
}

void ATower::BeginPlay()
{
	bSuperArmor = true; // 타워는 항시 슈퍼아머
	IsPlayerTeam = true; // 플레이어 팀
}

// 타워는 그냥 가장 가까운 적을 탐색한다.
AMiniCyphersCharacter* ATower::GetTarget()
{
	AMiniCyphersCharacter* Target;

	if (TryGetOverlapTarget(this, OUT Target) == false)
		return nullptr;

	return Target;
}

FVector ATower::GetMyLocation() const
{
	if (TowerStaticMesh)
	{
		return TowerStaticMesh->GetComponentLocation();
	}

	return GetActorLocation();
}