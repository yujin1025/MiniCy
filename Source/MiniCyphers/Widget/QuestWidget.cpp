// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "../MiniCyphersGameMode.h"
#include "Components/ListView.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	GameMode->OnChangedQuestDelegate.AddLambda([this](TArray<FQuestData*> QuestDatas, TMap<int, int> QuestProgressMap) -> void
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest Start"));
	});

	GameMode->TryChangePhase(0);
}
