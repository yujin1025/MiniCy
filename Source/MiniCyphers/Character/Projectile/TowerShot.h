// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersProjectile.h"
#include "../TimeShotComponent.h"
#include "TowerShot.generated.h"
/**
 * 
 */
UCLASS()
class MINICYPHERS_API ATowerShot : public AMiniCyphersProjectile
{
	GENERATED_BODY()

public:
	ATowerShot();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerShot")
	float TransparencyAmount = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimeShotComponent* TimeShotComponent;

	virtual void BeginPlay() override;
};
