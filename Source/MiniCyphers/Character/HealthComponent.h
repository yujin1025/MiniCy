// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerState.h"
#include "../Animation/AnimNotifyAttackState.h"
#include "MiniCyphersComponent.h"
#include "Engine/GameInstance.h"

#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDamaged, AMiniCyphersCharacter*, float, bool)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINICYPHERS_API UHealthComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

private:
	int MaxHealth;
	int CurrentHealth;

public:
	FOnDamaged OnDamaged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ChangeHealth(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int DamageAmount, float UpperVelocity, float KnockBackDistance, bool isMelee);

	UFUNCTION(BlueprintPure, Category = "Health")
	int GetCurrentHealth() const { return CurrentHealth; }	
};
