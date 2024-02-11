// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MiniCyphersGameState.generated.h"

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

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	// 퀘스트, 타이머, HP, 목숨, 웨이브 단계, 보스 등이 저장됩니다.

	//여기서는 보스가 죽었을때 뭘 할지 이런식으로 하려고 hp가 필요한거

private:
	// Quest Id - Progress
	TMap<int, int> QuestProgressDatas;
	int CurrentPhaseNumber = -1;

private:

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestPhaseTable;

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestTable;

public:
	TArray<FQuestPhaseData*> GetQuestPhaseDatas(int PhaseNumber);
	FQuestData* GetQuestData(int QuestId);
	TArray<FQuestData*> GetQuestDatas(int PhaseNumber);


public:
	bool TryChangePhase(int PhaseNumber);
	void OnChangedPhase(int PhaseNumber);

	bool TryCompleteQuest(int QuestId);
	void OnChangedQuest(int QuestId);

	FOnChangedQuestDelegate OnChangedQuestDelegate;

public:
	void OnChangedHealth(int ObjectID, float Amount);
};
