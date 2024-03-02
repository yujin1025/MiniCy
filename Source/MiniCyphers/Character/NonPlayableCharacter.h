// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersCharacter.h"
#include "NonPlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ANonPlayableCharacter : public AMiniCyphersCharacter
{
	GENERATED_BODY()

public:
	ANonPlayableCharacter();
	
public:
	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget) override;
};
