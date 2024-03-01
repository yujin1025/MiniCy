// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeActionComponent.h"
#include "TimeShotComponent.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UTimeShotComponent : public UTimeActionComponent
{
	GENERATED_BODY()
	
public:
	virtual void TryAction() override; 
};
