// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersPlayerController.h"
#include "MiniCyphersGameState.h"
#include "Character/MiniCyphersCharacter.h"
#include "Widget/MiniCyphersWidget.h"
#include "MiniCyphersPlayerState.h"
#include "Camera/PlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>



void AMiniCyphersPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMiniCyphersPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	OnPossessCharacter(Cast<AMiniCyphersCharacter>(aPawn));
}


void AMiniCyphersPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Settings", IE_Pressed, this, &AMiniCyphersPlayerController::OpenSettings);
	} 
}

void AMiniCyphersPlayerController::OpenSettings()
{
	if (SettingWidget && SettingWidget->IsInViewport())
	{
		return;
	}

	if (SettingsWidgetClass)
	{
		SettingWidget = CreateWidget<UMiniCyphersWidget>(GetWorld(), SettingsWidgetClass);

		if (SettingWidget != nullptr)
		{
			SettingWidget->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);
			bShowMouseCursor = true;
		}

	}

}

void AMiniCyphersPlayerController::CheckGameState()
{
    if (bGameStateShown)
        return;

    AMiniCyphersGameState* GameState = GetWorld()->GetGameState<AMiniCyphersGameState>();
    if (!GameState)
        return;

    if (GameState->IsDeadTrooper() || GameState->IsDeadTower())
    {
        if (GameState->IsDeadTrooper())
        {
            if (ClearWidgetClass)
            {
                GameClearWidget = CreateWidget<UMiniCyphersWidget>(GetWorld(), ClearWidgetClass);
                if (GameClearWidget != nullptr)
                {
                    GameClearWidget->AddToViewport();
                }
            }
        }

        if (GameState->IsDeadTower())
        {
            if (OverWidgetClass)
            {
                GameOverWidget = CreateWidget<UMiniCyphersWidget>(GetWorld(), OverWidgetClass);
                if (GameOverWidget != nullptr)
                {
                    GameOverWidget->AddToViewport();
                }
            }
        }

        SetPause(true);
        bShowMouseCursor = true;
        bGameStateShown = true;
    }
}

void AMiniCyphersPlayerController::OnPossessCharacter(AMiniCyphersCharacter* aCharacter)
{
	this->OwnerCharacter = aCharacter;
}

void AMiniCyphersPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckGameState();
}

AMiniCyphersPlayerState* AMiniCyphersPlayerController::GetState()
{
	return Cast<AMiniCyphersPlayerState>(PlayerState);
}

AMiniCyphersCharacter* AMiniCyphersPlayerController::GetCharacter()
{
	return OwnerCharacter;
}
