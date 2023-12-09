// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersPlayerState.h"

AMiniCyphersPlayerState::AMiniCyphersPlayerState()
{
}

void AMiniCyphersPlayerState::OnChangePlayerHealth(int objectId, int Amount)
{
	OnPlayerHPChanged.Broadcast(objectId, Amount);
}
