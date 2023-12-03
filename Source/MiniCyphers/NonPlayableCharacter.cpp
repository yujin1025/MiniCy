// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"
#include "MiniCyphersAIController.h"

ANonPlayableCharacter::ANonPlayableCharacter()
{
	// AIControllerClass = AMiniCyphersAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
