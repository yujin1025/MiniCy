// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"
#include "MiniCyphersAIController.h"

ANonPlayableCharacter::ANonPlayableCharacter()
{
	// BP에서 세팅하자.
	// AIControllerClass = AMiniCyphersAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}
