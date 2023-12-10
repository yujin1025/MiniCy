// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "../FieldItem/FieldItem.h"

#include "ItemActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UItemActionComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

public:
	bool IsSatisfiedCondition();
	void OnTrigger(EItemType ItemType);
};
