// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));

	RootComponent = StaticMesh;

}

void ATowerShot::BeginPlay()
{

	if (StaticMesh)
	{
		UMaterialInstanceDynamic* DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), TransparencyAmount);
		}
	}
}

