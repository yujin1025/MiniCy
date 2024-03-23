// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MiniCyphersCharacter.h"
#include "GameFramework/Actor.h"
#include "MiniCyphersProjectile.generated.h"

class AMiniCyphersCharacter;

UCLASS()
class MINICYPHERS_API AMiniCyphersProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiniCyphersProjectile();

public:
	AMiniCyphersCharacter* ProjectileOwner;
	FVector ProjectileDirection;

public:
	void Initialize(AMiniCyphersCharacter* Character);
	void SetDirection(FVector Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	int CurrentAttackCount = 0;

	UPROPERTY(EditAnywhere)
	int MaxAttackCount = 1;

	UPROPERTY(EditAnywhere)
	int DamageAmount;

	UPROPERTY(EditAnywhere)
	float KnockBackDistance = 50.0f;

	UPROPERTY(EditAnywhere)
	float UpperVelocity = 100.0f;

	UPROPERTY(EditAnywhere)
	bool IsMelee = false;

	UPROPERTY(EditAnywhere)
	float StiffTime = 5.0f;

	UPROPERTY(EditAnywhere)
	EDamageType DamageType = EDamageType::Stand;

	UPROPERTY(EditAnywhere)
	float TargetDetectRadius = 1000.0f;

	bool TryGetOverlapResult(AMiniCyphersCharacter* Character, TArray<FOverlapResult>& OverlapResults);

	bool TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Character, OUT AMiniCyphersCharacter*& FoundTarget);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
