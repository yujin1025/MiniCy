// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayableCharacter.h"
#include "Sentinel.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ASentinel : public ANonPlayableCharacter
{
	GENERATED_BODY()
	
public:
	ASentinel();

	virtual void BeginPlay() override;


};
