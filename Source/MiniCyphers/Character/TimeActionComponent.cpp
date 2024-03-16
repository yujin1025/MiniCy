// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActionComponent.h"

void UTimeActionComponent::BeginPlay()
{
	CurrentDeltaTime = 0.0f;
	StartAction();
}

void UTimeActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CurrentDeltaTime += DeltaTime;

	UpdateAction(DeltaTime);
	if (CurrentDeltaTime >= ReserveTime)
	{
		OnAction();
		CurrentDeltaTime = 0.0f;
	}
}

void UTimeActionComponent::StartAction()
{

}

void UTimeActionComponent::UpdateAction(float DeltaTime)
{
}

// 기본은 Owner Actor 삭제
void UTimeActionComponent::OnAction()
{
	GetOwner()->Destroy();
}
