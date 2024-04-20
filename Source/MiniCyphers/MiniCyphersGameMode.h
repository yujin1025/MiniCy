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
	Tower = 2,
	Sentinel = 3,
	Trooper = 4,
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

public:
	FCharacterStatData* GetStatData(ECharacterType type);

private:
	UPROPERTY(EditAnywhere)
	FVector PlayerSpawnPosition = FVector(-190.0f, -2110.0f, 0.0f);
	
	UPROPERTY(EditAnywhere)
	FRotator PlayerSpawnRotation = FRotator(0.0f, 0.0f, 90.0f);
	
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



