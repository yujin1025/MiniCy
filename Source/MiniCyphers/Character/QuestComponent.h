// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "QuestComponent.generated.h"

class AMiniCyphersGameMode;
class AMiniCyphersCharacter;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UQuestComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AMiniCyphersCharacter* GetCharacter();
};
