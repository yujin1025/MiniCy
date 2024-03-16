// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "TimeActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UTimeActionComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartAction();
	virtual void UpdateAction(float DeltaTime);
	virtual void OnAction();

protected:
	UPROPERTY(EditAnywhere)
	float ReserveTime = 5.0f;

	float CurrentDeltaTime = 0.0f;
};
