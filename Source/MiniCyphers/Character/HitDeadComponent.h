// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersComponent.h"
#include "HitDeadComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MINICYPHERS_API UHitDeadComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> HitMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> DeadMontages;

	int32 CurrentHitMontageIndex;
	int32 CurrentDeadMontageIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayHitMontage();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayDeadMontage();
};
