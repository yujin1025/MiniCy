// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "InputBlockComponent.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UInputBlockComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()
	
public:
	bool bInputBlock = false;
};
