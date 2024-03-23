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
	UPROPERTY(EditAnywhere)
	FLinearColor WarningAreaColor = FLinearColor::Red;
	
	ATowerShot();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimeShotComponent* TimeShotComponent;

	UMaterialInterface* MyMaterialInterface = nullptr;
	UMaterialInstanceDynamic* MyMaterialInterfaceDynamic = nullptr;

	float CurrentTransparencyAmount = 1.0f;

	void SetAlpha(float Alpha);
	void ChangeAlpha(float DeltaAlpha);
};
