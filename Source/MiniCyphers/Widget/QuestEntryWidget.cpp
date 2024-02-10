// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestEntryWidget.h"
#include "QuestWidget.h"
#include "QuestProgressData.h"
#include "../MiniCyphersGameMode.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

void UQuestEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto* ProgressData = Cast<UQuestProgressData>(ListItemObject);
	if (ProgressData == nullptr)
		return;

	SetQuestData(ProgressData->Progress, ProgressData->QuestData);
}

void UQuestEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UQuestEntryWidget::SetQuestData(int CurrentProgress, FQuestData* Data)
{
	FString CurrentProgressText = FString::FromInt(CurrentProgress);
	FString MaxProgressText = FString::FromInt(Data->MaxProgress);

	FText QuestDescription = FText::FromString(Data->Description + " (" + CurrentProgressText + "/" + MaxProgressText + ")");

	QuestDescriptionText->SetText(QuestDescription);
}
