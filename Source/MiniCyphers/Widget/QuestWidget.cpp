// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersGameState.h"
#include "QuestProgressData.h"
#include "Components/ListView.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "QuestEntryWidget.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	GameMode->MyGameState->OnChangedQuestDelegate.AddLambda([this](TArray<FQuestData*> QuestDatas, TMap<int, int> QuestProgressMap) -> void
	{
			ListView_18->ClearListItems();

			for (auto& QuestData : QuestDatas)
			{
				auto* Data = NewObject<UQuestProgressData>(this, UQuestProgressData::StaticClass());
				if (Data == nullptr)
					continue;
				
				Data->Progress = QuestProgressMap[QuestData->QuestId];
				Data->QuestData = QuestData;

				ListView_18->AddItem(Data);
			}
	});

	GameMode->MyGameState->TryChangePhase(0);
}
