// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "QuestWidget.generated.h"

class UListView;
struct FQuestData;
class AMiniCyphersGameMode;
class UQuestEntryWidget;
class UQuestProgressData;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UQuestWidget : public UMiniCyphersWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UListView> ListView_18;

protected:
	virtual void NativeConstruct() override;
};
