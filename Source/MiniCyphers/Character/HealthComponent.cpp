// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>
#include "MiniCyphersCharacter.h"
#include "../MiniCyphersGameInstance.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersGameState.h"
#include "../MiniCyphersPlayerState.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	auto* Data = GameMode->GetStatData(ECharacterType::Shiva);
	if (Data == nullptr)
		return;

	MaxHealth = Data->MaxHp;
	CurrentHealth = MaxHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ChangeHealth(AMiniCyphersCharacter* Attacker, int Amount, bool IsPlayer) //영향 받는 애가 플레이어인지 여부
{
	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	CurrentHealth += Amount;

	if (IsPlayer) //영향 받는 애가 플레이어
	{
		GameMode->MyPlayerState->OnChangePlayerHealth(0, CurrentHealth); // 플레이어 스테이트

		if (CurrentHealth <= 0)
		{
			auto Player = Cast<AMiniCyphersCharacter>(GetOwner());
			Player->OnDie();
		}
	}
	else //영향 받는 애가 플레이어 아님
	{
		GameMode->MyGameState->OnChangedHealth(0, CurrentHealth);
	}
	

	//UE_LOG(LogTemp, Warning, TEXT("%s current health: %d"), *GetName(), GetCurrentHealth());

}

