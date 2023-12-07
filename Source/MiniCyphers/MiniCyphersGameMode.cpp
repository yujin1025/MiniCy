// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniCyphersGameMode.h"
#include "Character/MiniCyphersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Widget/MiniCyphersWidget.h"
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
