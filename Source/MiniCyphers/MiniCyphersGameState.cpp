// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameState.h"
#include "Character/Sentinel.h"
#include "Character/Trooper.h"
#include "Character/Tower.h"
#include "Widget/MiniCyphersWidget.h"
#include "Character/MiniCyphersCharacter.h"
#include <Kismet/GameplayStatics.h>

AMiniCyphersGameState::AMiniCyphersGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMiniCyphersGameState::Spawn(ESpawnType SpawnType)
{
	AMiniCyphersCharacter* Character;

	switch (SpawnType)
	{
	case ESpawnType::Sentinel:
		
		if (SentinelSpawnPositions.Num() > CurrentSpawnSentinelPositionIndex)
		{
			Character = GetWorld()->SpawnActor<ASentinel>(SentinelClass, SentinelSpawnPositions[CurrentSpawnSentinelPositionIndex], SentinelSpawnRotation);
			Character->CharacterId = CurrentSentinelCharacterId;

			CurrentSpawnSentinelPositionIndex++;
			CurrentSpawnSentinelPositionIndex %= MaxFieldSentinelCount;

			MonsterHealthMap.Add(CurrentSentinelCharacterId, 100);
			CurrentSentinelCharacterId++;
		}

		break;

	case ESpawnType::Tower:
		Character = GetWorld()->SpawnActor<ATower>(TowerClass, TowerSpawnPosition, TowerSpawnRotation);		
		Character->CharacterId = TowerCharacterId;

		MonsterHealthMap.Add(TowerCharacterId, 100);

		break;

	case ESpawnType::Trooper:
		Character = GetWorld()->SpawnActor<ATrooper>(TrooperClass, TrooperSpawnPosition, TrooperSpawnRotation);
		Character->CharacterId = TrooperCharacterId;

		MonsterHealthMap.Add(TrooperCharacterId, 100);

		break;
	}
}

int AMiniCyphersGameState::GetDeadSentinelCount()
{
	int DeadSentinelCount = 0;

	for (auto& Pair : MonsterHealthMap)
	{
		// ¼¾Æ¼³ÚÀÌ¸é
		if (Pair.Key >- StartSentinelCharacterId)
		{
			if (Pair.Value <= 0)
			{
				DeadSentinelCount++;
			}
		}
	}

	return DeadSentinelCount;
}

void AMiniCyphersGameState::OnChangedHealth(int ObjectID, float CurrentHealth)
{
	if (MonsterHealthMap.Contains(ObjectID) == false)
		return;

	MonsterHealthMap[ObjectID] = CurrentHealth;
}

bool AMiniCyphersGameState::IsDeadTrooper()
{
	return MonsterHealthMap[TrooperCharacterId] <= 0;
}

bool AMiniCyphersGameState::IsDeadTower()
{
	return MonsterHealthMap[TowerCharacterId] <= 0;
}

void AMiniCyphersGameState::BeginPlay()
{
	Super::BeginPlay();

	Spawn(ESpawnType::Trooper);
	Spawn(ESpawnType::Tower);

	CurrentSentinelCharacterId = StartSentinelCharacterId;

	for (int i = 0; i < MaxFieldSentinelCount; i++)
	{
		Spawn(ESpawnType::Sentinel);
	}
}

void AMiniCyphersGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int FieldSentinelCount = 0;

	for (auto& Pair : MonsterHealthMap)
	{
		// ¼¾Æ¼³ÚÀÌ¸é
		if (Pair.Key >= StartSentinelCharacterId)
		{
			if (Pair.Value > 0)
			{
				FieldSentinelCount++;
			}
		}
	}

	if (FieldSentinelCount < MaxFieldSentinelCount)
	{
		for (int i = 0; i < FieldSentinelCount; i++)
		{
			Spawn(ESpawnType::Sentinel);
		}
	}

}
