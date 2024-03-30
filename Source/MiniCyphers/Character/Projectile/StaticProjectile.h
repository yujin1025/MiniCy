// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersProjectile.h"
#include "StaticProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AStaticProjectile : public AMiniCyphersProjectile
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	

};
