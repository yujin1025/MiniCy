// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldItem.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/ItemActionComponent.h"

// Sets default values
AFieldItem::AFieldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFieldItem::BeginPlay()
{
	Super::BeginPlay();
}

void AFieldItem::OnTrigger()
{
	Destroy();
}

// Called every frame
void AFieldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UItemActionComponent* DetectedTarget = nullptr;
	
	if (TryGetOverlapTarget(OUT DetectedTarget) == false)
		return;

	if (DetectedTarget->IsSatisfiedCondition() == false)
		return;

	DetectedTarget->OnTrigger(ItemType);
	OnTrigger();
}

bool AFieldItem::TryGetOverlapResult(TArray<FOverlapResult>& OverlapResults)
{
	auto* World = GetWorld();
	if (World == nullptr)
		return false;

	FVector Center = GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, this);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AreaRadius),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, AreaRadius, 16, FColor::Green, false, 0.2f);
	}

	return bResult;
}

bool AFieldItem::TryGetOverlapTarget(OUT UItemActionComponent*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			if (TargetCharacter->IsPlayerTeam == false)
				continue;

			auto* ItemActionComponent = TargetCharacter->GetComponentByClass<UItemActionComponent>();
			if (ItemActionComponent == nullptr)
				continue;

			bResult = true;
			FoundTarget = ItemActionComponent;
			break;
		}
	}

	return bResult;
}

AMiniCyphersCharacter* AFieldItem::GetCharacter(const FOverlapResult& OverlapResult)
{
	auto* Actor = OverlapResult.GetActor();
	if (Actor == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(Actor);
}
