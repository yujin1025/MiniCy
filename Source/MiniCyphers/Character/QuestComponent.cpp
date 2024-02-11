// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "MiniCyphersCharacter.h"
#include "../MiniCyphersGameMode.h"

void UQuestComponent::BeginPlay()
{
	auto* Character = GetCharacter();
	if (Character == nullptr)
		return;

	Character->OnMoveDelegate.AddLambda([this](FVector2D Value) -> void
	{
		auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode == nullptr)
			return;

		GameMode->TryCompleteQuest(0);
	});
}

AMiniCyphersCharacter* UQuestComponent::GetCharacter()
{
	return Cast<AMiniCyphersCharacter>(GetOwner());
}
