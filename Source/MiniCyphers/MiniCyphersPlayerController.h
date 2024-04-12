// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniCyphersPlayerController.generated.h"


class AMiniCyphersCharacter;
class AMiniCyphersPlayerState;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;
	void OpenSettings();
	void CheckGameState();

private:
	void OnPossessCharacter(AMiniCyphersCharacter* aCharacter);
	AMiniCyphersCharacter* OwnerCharacter;

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bGameStateShown = false;

public:
	AMiniCyphersPlayerState* GetState();
	AMiniCyphersCharacter* GetCharacter();

	UPROPERTY()
	class UMiniCyphersWidget* SettingWidget;

	UPROPERTY()
	UMiniCyphersWidget* GameClearWidget;

	UPROPERTY()
	UMiniCyphersWidget* GameOverWidget;

private:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UMiniCyphersWidget> ClearWidgetClass;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UMiniCyphersWidget> OverWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UMiniCyphersWidget> SettingsWidgetClass;
	
};
