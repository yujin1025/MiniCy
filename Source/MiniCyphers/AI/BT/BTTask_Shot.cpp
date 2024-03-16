// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shot.h"
#include "../MiniCyphersAIController.h"
#include "../../Character/MiniCyphersCharacter.h"
#include "../../Character/Projectile/TowerShot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_Shot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return EBTNodeResult::Failed;

	auto* Character = GetCharacter(OwnerComp);
	if (Character == nullptr)
		return EBTNodeResult::Failed;

	auto* Target = BlackBoard->GetValueAsObject(AMiniCyphersAIController::TargetObjectKey);
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	auto* TargetCharacter = Cast<AMiniCyphersCharacter>(Target);
	if (TargetCharacter == nullptr)
		return EBTNodeResult::Failed;

	UWorld* const World = GetWorld();

	FVector SpawnLocation = TargetCharacter->GetActorLocation();
	SpawnLocation.Z = 0;

	auto* Projectile = World->SpawnActor<ATowerShot>(ProjectileClass, SpawnLocation, FRotator::ZeroRotator);
	if (Projectile == nullptr)
		return EBTNodeResult::Failed;
	
	Projectile->Initialize(Character);
	return EBTNodeResult::Succeeded;
}
