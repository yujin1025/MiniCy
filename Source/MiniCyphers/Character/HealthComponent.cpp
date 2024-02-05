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

void UHealthComponent::ChangeHealth(AMiniCyphersCharacter* Attacker, int Amount)
{
	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	if (CurrentHealth <= 0)
		return;

	CurrentHealth += Amount;

	auto Character = Cast<AMiniCyphersCharacter>(GetOwner());

	if (Character->IsPlayer()) //영향 받는 애가 플레이어
	{
		GameMode->MyPlayerState->OnChangePlayerHealth(0, CurrentHealth); // 플레이어 스테이트

	}
	else //영향 받는 애가 플레이어 아님
	{
		GameMode->MyGameState->OnChangedHealth(0, CurrentHealth);
	}



	if (CurrentHealth <= 0)
	{
		Character->OnDie();
	}
	else
	{
		Character->OnHit(Attacker);
		//쳐맞은 애니메이션 재생
	}


}

