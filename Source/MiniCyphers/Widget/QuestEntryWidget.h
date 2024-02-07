// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "QuestEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UQuestEntryWidget : public UMiniCyphersWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UTextBlock* QuestDescriptionText;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeConstruct() override;

};
