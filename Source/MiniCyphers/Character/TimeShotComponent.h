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
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMiniCyphersProjectile> ProjectileClass;

	virtual void StartAction() override; 
	virtual void UpdateAction(float DeltaTime) override;

	virtual void OnAction() override;
};
