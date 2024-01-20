// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MiniCyphersComponent.h"
#include "Engine/GameInstance.h"

#include "HealthComponent.generated.h"



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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ChangeHealth(AMiniCyphersCharacter* Attacker, int Amount, bool IsPlayer); //인자: 때린놈, 데미지량, 맞은놈 플레이어인지 여부

	UFUNCTION(BlueprintPure, Category = "Health")
	int GetCurrentHealth() const { return CurrentHealth; }	
};
