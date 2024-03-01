// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	UMaterialInstanceDynamic* MaterialInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("Alpha"), DefaultAlphaValue);
	}
}
