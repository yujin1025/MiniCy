// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameState.h"

void AMiniCyphersGameState::OnChangedHealth(int ObjectID, float Amount)
{

	if (Amount <= 0.0)
	{
		AActor* Actor = GetOwner();
		if (Actor)
		{
			//Actor->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Destroyed!"));
			//쳐맞은애(몬스터)피가 0 이하면 파괴 메세지
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NonPlayer Current Health: %f"), Amount);
	}
}
