// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniCyphersGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, int)

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMiniCyphersGameInstance();
	void OnChangePlayerHealth(int objectId, int Amount);

protected:
	virtual void Init() override;

public:
	FOnHPChangedDelegate OnPlayerHPChanged;

};
