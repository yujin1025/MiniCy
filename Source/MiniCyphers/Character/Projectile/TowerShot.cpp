// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	
	// 이곳에서 루트로 지정하기 때문에 트랜스폼을 움직일 수 없음
	RootComponent = StaticMesh;

	// 트랜스폼을 지정하고 싶다면, 하위에 Static Mesh를 CreateDefaultSubobject를 통해 만들고,
	// BP에서 직접 위치 값을 정하면 됨
	// 그럼 당연히 아래 BeginPlay 코드 내용도 StaticMesh에서 ShotMesh 등으로 바뀌어야 함

}

void ATowerShot::BeginPlay()
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
			DynamicMaterialInstance->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.1f);
		}

		// 스태틱 메시 내 메터리얼에 정보 인스턴스 적용
		StaticMesh->SetMaterial(0, DynamicMaterialInstance);
	}
}

