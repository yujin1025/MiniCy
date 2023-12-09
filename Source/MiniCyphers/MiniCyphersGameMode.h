// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniCyphersGameMode.generated.h"

class AMiniCyphersGameState;
class AMiniCyphersPlayerState;
class AMiniCyphersPlayerController;

class UMiniCyphersWidget;
class APlayerController;

UCLASS(minimalapi)
class AMiniCyphersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMiniCyphersGameMode();

	virtual void BeginPlay() override;

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	void OpenWidget();
	void OnPostLogin(AMiniCyphersPlayerController* NewPlayer);

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UMiniCyphersWidget> InGameWindowWidgetClass;

	UPROPERTY()
	UMiniCyphersWidget* InGameWindowWidget;

public:
	UPROPERTY()
	AMiniCyphersGameState* MyGameState;

	UPROPERTY()
	AMiniCyphersPlayerState* MyPlayerState;
};



