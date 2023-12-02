// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


AMiniCyphersAIController::AMiniCyphersAIController()
{
	RepeatInterval = 3.0f;
}

void AMiniCyphersAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AMiniCyphersAIController::OnRepeatTimer, RepeatInterval, true);
}

void AMiniCyphersAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AMiniCyphersAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr)
		return;

	auto NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		UE_LOG(LogTemp, Log, TEXT("»ý°¢ Áß?"));
	}
}
