// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniCyphersGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMiniCyphersGameInstance();

protected:
	virtual void Init() override;

private:
	const static FName TitleLevelName;
	const static FName InGameLevelName;

public:
	void OpenLevel(FName LevelName) const;

};
