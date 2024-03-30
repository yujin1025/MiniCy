// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sentinel.h"
#include "BombSentinel.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ABombSentinel : public ASentinel
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void UpdateTarget() override;

};
