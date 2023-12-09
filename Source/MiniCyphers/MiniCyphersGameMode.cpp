// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniCyphersGameMode.h"
#include "Character/MiniCyphersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Widget/MiniCyphersWidget.h"
#include "Blueprint/UserWidget.h"
#include "MiniCyphersPlayerController.h"
#include "MiniCyphersPlayerState.h"
#include "MiniCyphersGameState.h"
#include "Character/Shiva.h"
#include "MiniCyphersPlayerController.h"

AMiniCyphersGameMode::AMiniCyphersGameMode()
{
	DefaultPawnClass = AShiva::StaticClass(); // 런타임에 수정됨

	PlayerControllerClass = AMiniCyphersPlayerController::StaticClass();
	PlayerStateClass = AMiniCyphersPlayerState::StaticClass();
	GameStateClass = AMiniCyphersGameState::StaticClass();
}

void AMiniCyphersGameMode::BeginPlay()
{
	OpenWidget();
}

void AMiniCyphersGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MyGameState = Cast<AMiniCyphersGameState>(GameStateClass);
}

void AMiniCyphersGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	OnPostLogin(Cast<AMiniCyphersPlayerController>(NewPlayer));
}

void AMiniCyphersGameMode::OpenWidget()
{
	InGameWindowWidget = CreateWidget<UMiniCyphersWidget>(GetWorld(), InGameWindowWidgetClass);
	if (InGameWindowWidget != nullptr)
	{
		InGameWindowWidget->AddToViewport();
	}
}

void AMiniCyphersGameMode::OnPostLogin(AMiniCyphersPlayerController* NewPlayer)
{
}
