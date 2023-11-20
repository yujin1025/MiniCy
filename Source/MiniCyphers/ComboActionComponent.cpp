// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboActionComponent.h"

// Sets default values for this component's properties
UComboActionComponent::UComboActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComboActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetCombo();
}


// Called every frame
void UComboActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComboActionComponent::ResetCombo()
{
	CurrentComboIndex = 0;
	CanCombo = false;
}

void UComboActionComponent::DoCombo()
{
	if (ComboMontages.IsValidIndex(CurrentComboIndex) == false || CanCombo == false) // 콤보가 불가능하다면 무조건 1번 몽타주 실행
		ResetCombo();
	
	auto nextMontage = ComboMontages[CurrentComboIndex++];
	if (nextMontage == nullptr)
		return;

	auto character = this->GetCyphersCharacter();
	if (character == nullptr)
		return;

	character->PlayAnimMontage(nextMontage);

	CanCombo = true;
}

