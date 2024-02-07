// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniCyphers/MiniCyphersGameInstance.h"
#include "MiniCyphersGameMode.generated.h"

class AMiniCyphersGameState;
class AMiniCyphersPlayerState;
class AMiniCyphersPlayerController;

class UMiniCyphersWidget;
class APlayerController;

UENUM()
enum class ECharacterType
{
	Shiva = 0,
	Tara = 1,
	Max,
};

USTRUCT(BlueprintType)
struct FCharacterStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStatData() : MaxHp(100), MoveSpeed(5) {}

	UPROPERTY()
	int32 MaxHp;

	UPROPERTY()
	int32 MoveSpeed;
};

USTRUCT(BlueprintType)
struct FQuestPhaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FQuestPhaseData() {}

	UPROPERTY()
	int32 QuestId;

	UPROPERTY()
	int32 PhaseNumber;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FQuestData() {}

	UPROPERTY()
	int32 QuestId;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	int32 MaxProgress;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChangedQuestDelegate, TArray<FQuestData*>, TMap<int, int>)

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
	virtual void StartPlay() override;

private:
	void OpenWidget();
	void OnPostLogin(AMiniCyphersPlayerController* NewPlayer);
	void SpawnPlayer(ECharacterType Type);

private:
	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* CharacterStatTable;

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestPhaseTable;

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestTable;

private:
	// Quest Id - Progress
	TMap<int, int> QuestProgressDatas;
	int CurrentPhaseNumber = -1;

public:
	FCharacterStatData* GetStatData(ECharacterType type);
	TArray<FQuestPhaseData*> GetQuestPhaseDatas(int PhaseNumber);
	FQuestData* GetQuestData(int QuestId);
	TArray<FQuestData*> GetQuestDatas(int PhaseNumber);

public:
	bool TryChangePhase(int PhaseNumber);
	void OnChangedPhase(int PhaseNumber);

	bool TryCompleteQuest(int QuestId);
	void OnChangedQuest(int QuestId);

	FOnChangedQuestDelegate OnChangedQuestDelegate;

private:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UMiniCyphersWidget> InGameWindowWidgetClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class ATara> TaraClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AShiva> ShivaClass;

public:
	UPROPERTY()
	UMiniCyphersWidget* InGameWindowWidget;

	UPROPERTY()
	AMiniCyphersGameState* MyGameState;

	UPROPERTY()
	AMiniCyphersPlayerState* MyPlayerState;
};



