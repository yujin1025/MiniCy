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
	TArray<UAnimMontage*> StandHitMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AirborneHitMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> PowerKnockBackMontages;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeadMontage;

	int32 CurrentHitMontageIndex;
	int32 CurrentPowerKnockBackMontageIndex;
	int32 CurrentAirborneHitMontageIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayHitMontage(EDamageType DamageType);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayDeadMontage();

	bool bHit = false;
	bool bDead = false;
};
