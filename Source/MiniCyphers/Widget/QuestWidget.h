// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "QuestWidget.generated.h"

class UListView;
struct FQuestData;
class AMiniCyphersGameMode;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UQuestWidget : public UMiniCyphersWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UListView* ListView;

	UPROPERTY(EditAnyWhere)
	UMiniCyphersWidget* ListViewEntry;

protected:
	virtual void NativeConstruct() override;
};
