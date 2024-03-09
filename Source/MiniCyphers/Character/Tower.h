// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ATower : public ANonPlayableCharacter
{
	GENERATED_BODY()
	
public:
	ATower();
	virtual void BeginPlay() override;
	
	virtual AMiniCyphersCharacter* GetTarget() override;
};
