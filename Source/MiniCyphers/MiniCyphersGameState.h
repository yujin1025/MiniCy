// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MiniCyphersGameState.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	// 퀘스트, 타이머, HP, 목숨, 웨이브 단계, 보스 등이 저장됩니다.

	//여기서는 보스가 죽었을때 뭘 할지 이런식으로 하려고 hp가 필요한거

private:
	float CurrentHP;

public:
	void OnChangedHealth(int ObjectID, float Amount);
};
