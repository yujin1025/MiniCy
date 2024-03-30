// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersProjectile.h"
#include "StaticProjectile.generated.h"

class UTimeActionComponent;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AStaticProjectile : public AMiniCyphersProjectile
{
	GENERATED_BODY()

public:
	AStaticProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimeActionComponent* TimeActionComponent;

protected:
	virtual void Tick(float DeltaTime) override;
	

};
