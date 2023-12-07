// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MiniCyphersCharacter.h"

#include "MiniCyphersComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINICYPHERS_API UMiniCyphersComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMiniCyphersComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AMiniCyphersCharacter* GetCyphersCharacter()
	{
		auto owner = this->GetOwner();
		if (owner == nullptr)
			return nullptr;

		return Cast<AMiniCyphersCharacter>(owner);
	}

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
