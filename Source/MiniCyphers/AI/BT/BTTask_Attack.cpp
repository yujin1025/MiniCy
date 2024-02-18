// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/HealthComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;

	bIsProcessing = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto* Character = GetCharacter(OwnerComp);
	if (Character == nullptr)
		return EBTNodeResult::Failed;

	Character->UseSkill(AttackType);
	Character->OnUseSkillDelegate.AddLambda([this](EAttackType AttackType) -> void
	{
		bIsProcessing = true;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsProcessing)
	{
		GetAttack(OwnerComp);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	bIsProcessing = false;
}

void UBTTask_Attack::GetAttack(UBehaviorTreeComponent& OwnerComp)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return;

	auto TargetObject = BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey);
	if (TargetObject == nullptr)
		return;

	auto* TargetCharacter = Cast<AMiniCyphersCharacter>(TargetObject);
	if (TargetCharacter == nullptr)
		return;

	UHealthComponent* HealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
		return;

	auto* AIAttacker = GetCharacter(OwnerComp);
	if (AIAttacker == nullptr)
		return;

	HealthComponent->ChangeHealth(AIAttacker, -10);
}
