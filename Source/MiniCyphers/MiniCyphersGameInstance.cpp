// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameInstance.h"

UMiniCyphersGameInstance::UMiniCyphersGameInstance()
{
}

void UMiniCyphersGameInstance::Init()
{
	Super::Init();
}

void UMiniCyphersGameInstance::OnChangePlayerHealth(int objectId, int Amount)
{
	OnPlayerHPChanged.Broadcast(objectId, Amount);
}
