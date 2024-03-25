// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersPlayerController.h"
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

			FInputModeGameAndUI  InputMode;
			InputMode.SetWidgetToFocus(SettingWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			SetInputMode(InputMode);
		}

	}

}

void AMiniCyphersPlayerController::OnPossessCharacter(AMiniCyphersCharacter* aCharacter)
{
	this->OwnerCharacter = aCharacter;
}

AMiniCyphersPlayerState* AMiniCyphersPlayerController::GetState()
{
	return Cast<AMiniCyphersPlayerState>(PlayerState);
}

AMiniCyphersCharacter* AMiniCyphersPlayerController::GetCharacter()
{
	return OwnerCharacter;
}
