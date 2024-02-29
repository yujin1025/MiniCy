// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsLowHealth.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "../../Character/HealthComponent.h"

UBTDecorator_IsLowHealth::UBTDecorator_IsLowHealth()
{
    NodeName = TEXT("LowHeath");

}

bool UBTDecorator_IsLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return false;

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return false;

	UHealthComponent* HealthComponent = MyCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
		return false;

	int CurrentHealth = HealthComponent->GetCurrentHealth();
	return (CurrentHealth >= MinHealth && CurrentHealth <= MaxHealth);
}
