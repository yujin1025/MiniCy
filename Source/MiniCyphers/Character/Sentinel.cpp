// Fill out your copyright notice in the Description page of Project Settings.


#include "Sentinel.h"
#include "Kismet/GameplayStatics.h"
#include "../AI/MiniCyphersAIController.h"
#include "Tower.h"


ASentinel::ASentinel()
{
	// AIControllerClass = BP로 된 센티넬 AI Controller를 넣어줄 것
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ASentinel::BeginPlay()
{
	Super::BeginPlay();
	
	// 센티넬은 초기 슈퍼아머 없음
	bSuperArmor = false;
}