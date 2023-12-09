// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameInstance.h"
#include "Engine/DataTable.h"

UMiniCyphersGameInstance::UMiniCyphersGameInstance()
{
}

void UMiniCyphersGameInstance::Init()
{
	Super::Init();
}

FCharacterStatData* UMiniCyphersGameInstance::GetStatData(ECharacterType type)
{
	int typeInt = (int)type;
	FName typeString = *FString::FromInt(typeInt);

	return CharacterStatTable->FindRow<FCharacterStatData>(typeString, TEXT(""));
}