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
#include "Character/Tara.h"
#include "MiniCyphersPlayerController.h"
#include "MiniCyphersSaveGame.h"
#include "MiniCyphers/MiniCyphersGameInstance.h"
#include <Kismet/GameplayStatics.h>


AMiniCyphersGameMode::AMiniCyphersGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AMiniCyphersPlayerController::StaticClass();
	PlayerStateClass = AMiniCyphersPlayerState::StaticClass();
	GameStateClass = AMiniCyphersGameState::StaticClass();
}

void AMiniCyphersGameMode::BeginPlay()
{
	Super::BeginPlay();

	OpenWidget();
}

void AMiniCyphersGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MyGameState = Cast<AMiniCyphersGameState>(GameState);
}

void AMiniCyphersGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	OnPostLogin(Cast<AMiniCyphersPlayerController>(NewPlayer));
}

void AMiniCyphersGameMode::StartPlay()
{
	Super::StartPlay();

	auto* Data = UMiniCyphersSaveGame::Load();
	if (Data == nullptr)
		return;
	
	SpawnPlayer(Data->SelectedCharacterType);
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
	MyPlayerState = NewPlayer->GetState();
}

void AMiniCyphersGameMode::SpawnPlayer(ECharacterType Type)
{
	AMiniCyphersCharacter* Character = nullptr;
	switch (Type)
	{
	case ECharacterType::Shiva:
		Character = GetWorld()->SpawnActor<AShiva>(ShivaClass, PlayerSpawnPosition, PlayerSpawnRotation);
		break;
	case ECharacterType::Tara:
		Character = GetWorld()->SpawnActor<ATara>(TaraClass, PlayerSpawnPosition, PlayerSpawnRotation);
		break;
	}

	if (Character == nullptr)
		return;

	// �÷��̾� ��Ʈ�ѷ� ���
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController == nullptr)
		return;

	PlayerController->Possess(Character);
}

FCharacterStatData* AMiniCyphersGameMode::GetStatData(ECharacterType type)
{
	int typeInt = (int)type;
	FName typeString = *FString::FromInt(typeInt);

	return CharacterStatTable->FindRow<FCharacterStatData>(typeString, TEXT(""));
}

