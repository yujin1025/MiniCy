// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "SoundComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MINICYPHERS_API USoundComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TArray<UAudioComponent*> AudioComponents;

public:
	UFUNCTION(BlueprintCallable, Category = "Sound")
	virtual void PlaySoundEffect();
};
