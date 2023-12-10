// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FieldItem.h"
#include "AttackReinforceFieldItem.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AAttackReinforceFieldItem : public AFieldItem
{
	GENERATED_BODY()

public:
	AAttackReinforceFieldItem();

protected:
	virtual void OnTrigger() override;
	
};
