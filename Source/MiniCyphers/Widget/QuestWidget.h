// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "QuestWidget.generated.h"

class UListView;

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

protected:
	virtual void NativeConstruct() override;
};
