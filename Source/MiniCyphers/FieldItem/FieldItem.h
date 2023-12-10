// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldItem.generated.h"

class AMiniCyphersCharacter;
class UItemActionComponent;

UENUM()
enum class EItemType : uint8
{
	AttackReinforce = 0,
	DefenseReinforce = 1,
};

UCLASS()
class MINICYPHERS_API AFieldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnTrigger();
	AMiniCyphersCharacter* GetCharacter(const FOverlapResult& OverlapResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool TryGetOverlapResult(TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTarget(OUT UItemActionComponent*& FoundTarget);

private:
	UPROPERTY(EditAnywhere)
	float AreaRadius = 100.0f;

protected:
	EItemType ItemType;
};
