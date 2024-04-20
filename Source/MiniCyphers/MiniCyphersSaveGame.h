// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MiniCyphers/MiniCyphersGameInstance.h"
#include "MiniCyphersGameMode.h"
#include "MiniCyphersSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static const FString SlotName;
	static const int SlotIndex;

	static UMiniCyphersSaveGame* Create();
	static UMiniCyphersSaveGame* Load();

public:
	UMiniCyphersSaveGame();
	bool Save();

public:
	ECharacterType SelectedCharacterType;
	// 저장해야 할 데이터들 목록...
};
