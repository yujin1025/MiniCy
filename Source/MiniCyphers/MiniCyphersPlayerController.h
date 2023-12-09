// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniCyphersPlayerController.generated.h"

class AMiniCyphersCharacter;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	void OnPossessCharacter(AMiniCyphersCharacter* aCharacter);
};
