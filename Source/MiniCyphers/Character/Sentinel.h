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

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* NormalSentinel;
	
public:
	ASentinel();

protected:
	virtual void OnUseNormalAttack() override;

};
