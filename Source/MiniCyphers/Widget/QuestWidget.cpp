// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "../MiniCyphersGameMode.h"
#include "Components/ListView.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "QuestEntryWidget.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	GameMode->OnChangedQuestDelegate.AddLambda([this](TArray<FQuestData*> QuestDatas, TMap<int, int> QuestProgressMap) -> void
	{
			UQuestEntryWidget* Entry = NewObject<UQuestEntryWidget>(this, UQuestEntryWidget::StaticClass());
			ListView_18->AddItem(Entry);
	});

	GameMode->TryChangePhase(0);
}
