// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UMiniCyphersSaveGame::SlotName(TEXT("MiniCyphersSaveGame"));
const int UMiniCyphersSaveGame::SlotIndex(0);

UMiniCyphersSaveGame::UMiniCyphersSaveGame()
{
	
}

bool UMiniCyphersSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, SlotIndex);
}

UMiniCyphersSaveGame* UMiniCyphersSaveGame::Load()
{
	auto* SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	if (SaveGame == nullptr)
		return GetMutableDefault<UMiniCyphersSaveGame>();

	return Cast<UMiniCyphersSaveGame>(SaveGame);
}

UMiniCyphersSaveGame* UMiniCyphersSaveGame::Create()
{
	return NewObject<UMiniCyphersSaveGame>();
}
