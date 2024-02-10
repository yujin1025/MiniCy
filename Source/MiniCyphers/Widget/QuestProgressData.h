// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MiniCyphersGameMode.h"
#include "QuestProgressData.generated.h"

struct FQuestData;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UQuestProgressData : public UObject
{
	GENERATED_BODY()
	
public:
	int Progress;
	FQuestData* QuestData;
};
