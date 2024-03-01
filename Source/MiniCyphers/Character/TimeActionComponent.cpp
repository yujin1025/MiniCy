// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActionComponent.h"

void UTimeActionComponent::BeginPlay()
{
	CurrentDeltaTime = 0.0f;
}

void UTimeActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CurrentDeltaTime += DeltaTime;

	if (CurrentDeltaTime >= ReserveTime)
	{
		TryAction();
		OnAction();

		CurrentDeltaTime = 0.0f;
	}
}

void UTimeActionComponent::TryAction()
{

}

void UTimeActionComponent::OnAction()
{
	GetOwner()->Destroy();
}
