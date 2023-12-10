// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameInstance.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"

static FName TitleLevelName(TEXT("Title"));
static FName InGameLevelName(TEXT("InGame"));

UMiniCyphersGameInstance::UMiniCyphersGameInstance()
{

}

void UMiniCyphersGameInstance::Init()
{
	Super::Init();
}

void UMiniCyphersGameInstance::OpenLevel(FName LevelName) const 
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}