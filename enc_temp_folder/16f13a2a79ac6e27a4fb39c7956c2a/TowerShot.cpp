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
	Super::BeginPlay();
	SetAlpha(1.0f);
}

void ATowerShot::SetAlpha(float alpha)
{
	if (StaticMesh)
	{
		// 현재 메시의 0번 메터리얼을 가져온다.
		auto* BaseMaterial = StaticMesh->GetMaterial(0);

		// 베이스 메터리얼 기반으로 정보 인스턴스를 생성
		auto* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		if (DynamicMaterialInstance)
		{
			// Transparency_Amount라는 이름의 파라미터 값을 세팅
			DynamicMaterialInstance->SetScalarParameterValue(TEXT("Transparency_Amount"), alpha);
		}

		CurrentTransparencyAmount = alpha;
		// 스태틱 메시 내 메터리얼에 정보 인스턴스 적용
		StaticMesh->SetMaterial(0, DynamicMaterialInstance);
	}
}

void ATowerShot::ChangeAlpha(float DeltaAlpha)
{
	float NewAlpha = CurrentTransparencyAmount + DeltaAlpha;
	NewAlpha = NewAlpha > 0 ? NewAlpha : 0;
	NewAlpha = NewAlpha > 1 ? 1 : NewAlpha;
	SetAlpha(NewAlpha);
}

