// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Engine/GameInstance.h"
#include "../MiniCyphersGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_19")));

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	GameMode->MyPlayerState->OnPlayerHPChanged.AddLambda([this](int id, float amount) -> void
	{
		float PercentValue = amount / 100.0f;
		ProgressBar->SetPercent(PercentValue);
	});
}