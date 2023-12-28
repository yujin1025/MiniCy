// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "ProjectileEffect.h"  //프로젝타일에 추가로 부착되는 이펙트를 위한 클래스를 만들었었네요... 충격파 자리에 이펙트 생성 기능 등을 위함
//아마 캐릭터도 여기에 인클루드 해야겠죠?
#include "MiniCyphersProjectile.generated.h"

UCLASS()
class MINICYPHERS_API AMiniCyphersProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiniCyphersProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
