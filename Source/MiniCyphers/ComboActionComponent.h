// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MiniCyphersComponent.h"
#include "ComboActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINICYPHERS_API UComboActionComponent : public UMiniCyphersComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboActionComponent();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> ComboMontages;
	int CurrentComboIndex = 0;
	bool CanCombo = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ResetCombo();
	virtual void DoCombo();
};
