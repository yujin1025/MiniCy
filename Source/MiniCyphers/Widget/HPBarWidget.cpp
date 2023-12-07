// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Engine/GameInstance.h"
#include "../MiniCyphersGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UHPBarWidget::NativeConstruct()
{
	auto GameInstance = Cast<UMiniCyphersGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
		return;

	GameInstance->OnPlayerHPChanged.AddLambda([this](int id, int amount) -> void
	{
		ProgressBar->SetPercent(amount);
	});
}