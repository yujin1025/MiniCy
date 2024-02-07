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
	// 액터 스폰 위치 및 회전 지정
	FVector SpawnLocation = FVector(900.0f, 1110.0f, 90.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	AMiniCyphersCharacter* Character = nullptr;
	switch (Type)
	{
	case ECharacterType::Shiva:
		Character = GetWorld()->SpawnActor<AShiva>(ShivaClass, SpawnLocation, SpawnRotation);
		break;
	case ECharacterType::Tara:
		Character = GetWorld()->SpawnActor<ATara>(TaraClass, SpawnLocation, SpawnRotation);
		break;
	}

	if (Character == nullptr)
		return;

	// 플레이어 컨트롤러 얻기
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

TArray<FQuestPhaseData*> AMiniCyphersGameMode::GetQuestPhaseDatas(int PhaseNumber)
{
	TArray<FQuestPhaseData*> PhaseDatas;

	QuestPhaseTable->GetAllRows(TEXT(""), OUT PhaseDatas);

	return PhaseDatas;
}

FQuestData* AMiniCyphersGameMode::GetQuestData(int QuestId)
{
	TArray<FQuestData*> QuestDatas;

	QuestTable->GetAllRows(TEXT(""), OUT QuestDatas);

	for (auto& QuestData : QuestDatas)
	{
		if (QuestData->QuestId != QuestId)
			continue;

		return QuestData;
	}

	return nullptr;
}

TArray<FQuestData*> AMiniCyphersGameMode::GetQuestDatas(int PhaseNumber)
{
	TArray<FQuestPhaseData*> PhaseDatas = GetQuestPhaseDatas(PhaseNumber);
	TArray<FQuestData*> QuestDatas;

	for (auto& PhaseData : PhaseDatas)
	{
		FQuestData* QuestData = GetQuestData(PhaseData->QuestId);
		if (QuestData == nullptr)
			continue;

		QuestDatas.Add(QuestData);
	}

	return QuestDatas;
}

bool AMiniCyphersGameMode::TryChangePhase(int NextPhaseNumber)
{
	if (CurrentPhaseNumber >= 0)
	{
		TArray<FQuestData*> QuestDatas = GetQuestDatas(CurrentPhaseNumber);

		for (auto& QuestData : QuestDatas)
		{
			int32* QuestProgress = QuestProgressDatas.Find(QuestData->QuestId);
			if (QuestProgress == nullptr)
				continue;

			int Progress = *(QuestProgress);
			if (Progress >= QuestData->MaxProgress)
				continue;

			return false;
		}
	}
	
	CurrentPhaseNumber = NextPhaseNumber;
	OnChangedPhase(NextPhaseNumber);
	return true;
}

void AMiniCyphersGameMode::OnChangedPhase(int PhaseNumber)
{
	TArray<FQuestData*> QuestDatas = GetQuestDatas(PhaseNumber);
	
	QuestProgressDatas.Reset();
	for (auto& QuestData : QuestDatas)
	{
		QuestProgressDatas.Add(QuestData->QuestId, 0);
	}

	OnChangedQuestDelegate.Broadcast(QuestDatas, QuestProgressDatas);
}

bool AMiniCyphersGameMode::TryCompleteQuest(int QuestId)
{
	FQuestData* QuestData = GetQuestData(QuestId);
	if (QuestData == nullptr)
		return false;

	int32* QuestProgress = QuestProgressDatas.Find(QuestId);
	if (QuestProgress == nullptr)
		return false;

	int Progress = *(QuestProgress);
	if (Progress >= QuestData->MaxProgress)
		return false;

	QuestProgressDatas[QuestId]++;
	OnChangedQuest(QuestId);
	return true;
}

void AMiniCyphersGameMode::OnChangedQuest(int QuestId)
{
	TArray<FQuestData*> QuestDatas = GetQuestDatas(CurrentPhaseNumber);
	OnChangedQuestDelegate.Broadcast(QuestDatas, QuestProgressDatas);
}
