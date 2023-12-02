// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniCyphersGameMode.h"
#include "MiniCyphersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MiniCyphersWidget.h"
#include "Blueprint/UserWidget.h"

AMiniCyphersGameMode::AMiniCyphersGameMode()
{
	
}

void AMiniCyphersGameMode::BeginPlay()
{
	ingameWindowWidget = CreateWidget<UMiniCyphersWidget>(GetWorld(), ingameWindowWidgetClass);
	if (ingameWindowWidget != nullptr)
	{
		ingameWindowWidget->AddToViewport();
	}
}
