// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniCyphersGameMode.generated.h"

UCLASS(minimalapi)
class AMiniCyphersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMiniCyphersGameMode();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UMiniCyphersWidget> ingameWindowWidgetClass;

	UPROPERTY()
	UMiniCyphersWidget* ingameWindowWidget;
};



