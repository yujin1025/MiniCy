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
	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> StandHitMontages;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AirborneHitMontage;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* PowerKnockBackMontage;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeadMontage;

	int32 CurrentHitMontageIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void OnHit(EDamageType DamageType);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void OnDead();

	// Hit 모션 상태
	bool bHit = false;

	// Dead 모션 상태
	bool bDead = false;
};
