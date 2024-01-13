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
		}
	}
}
