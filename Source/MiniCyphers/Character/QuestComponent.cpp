// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "MiniCyphersCharacter.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersGameState.h"

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
}

AMiniCyphersCharacter* UQuestComponent::GetCharacter()
{
	return Cast<AMiniCyphersCharacter>(GetOwner());
}
