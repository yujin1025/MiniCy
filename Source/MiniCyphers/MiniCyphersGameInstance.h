// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniCyphersGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, int)

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
	FCharacterStatData() : MaxHp(100.0f), MoveSpeed(5.0f) {}

	UPROPERTY()
	int32 MaxHp;

	UPROPERTY()
	int32 MoveSpeed;
};

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMiniCyphersGameInstance();

private:
	UPROPERTY(EditAnywhere)
	class UDataTable* CharacterStatTable;

protected:
	virtual void Init() override;

public:
	FOnHPChangedDelegate OnPlayerHPChanged;

public:
	void OnChangePlayerHealth(int objectId, int Amount);
	FCharacterStatData* GetStatData(ECharacterType type);
};
