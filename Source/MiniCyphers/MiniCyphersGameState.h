// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MiniCyphersGameState.generated.h"

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	Sentinel,
	Trooper,
	Tower,
};


/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	// 퀘스트, 타이머, HP, 목숨, 웨이브 단계, 보스 등이 저장됩니다.

	// 여기서는 보스가 죽었을때 뭘 할지 이런식으로 하려고 hp가 필요한거

public:
	AMiniCyphersGameState();

private:
	int TrooperCharacterId = 0;
	int TowerCharacterId = 1;

	int StartSentinelCharacterId = 2;
	int CurrentSentinelCharacterId = 2;

private:
	UPROPERTY(EditAnywhere)
	TArray<FVector> SentinelSpawnPositions;

	UPROPERTY(EditAnywhere)
	FRotator SentinelSpawnRotation;

	UPROPERTY(EditAnywhere)
	FVector TrooperSpawnPosition;

	UPROPERTY(EditAnywhere)
	FRotator TrooperSpawnRotation;

	UPROPERTY(EditAnywhere)
	FVector TowerSpawnPosition;

	UPROPERTY(EditAnywhere)
	FRotator TowerSpawnRotation;

private:
	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> TrooperClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> TowerClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> SentinelClass;

private:
	TMap<int, int> MonsterHealthMap;
	int MaxFieldSentinelCount = 2;
	int CurrentSpawnSentinelPositionIndex = 0;

public:
	void OnChangedHealth(int ObjectID, float CurrentHealth);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	int GetDeadSentinelCount();
	bool IsDeadTrooper();
	bool IsDeadTower();

private:
	void Spawn(ESpawnType SpawnType);
};
