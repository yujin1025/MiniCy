// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersProjectile.h"
#include "../../Character/MiniCyphersCharacter.h"

// Sets default values
AMiniCyphersProjectile::AMiniCyphersProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMiniCyphersProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}
bool AMiniCyphersProjectile::TryGetOverlapResult(AMiniCyphersCharacter* Character, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = GetWorld();
	if (World == nullptr)
		return false;

	FVector Center = GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Character);
	CollisionParam.AddIgnoredActor(this);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(TargetDetectRadius),
		CollisionParam);

	DrawDebugSphere(World, Center, TargetDetectRadius, 16, FColor::Red, false, 0.2f);
	return bResult;
}

bool AMiniCyphersProjectile::TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets)
{
	TArray<FOverlapResult> OverlapResults;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = Cast<AMiniCyphersCharacter>(OverlapResult.GetActor());
			if (TargetCharacter == nullptr)
				continue;

			if (Character->IsPlayerTeam != TargetCharacter->IsPlayerTeam)
			{
				FoundTargets.Add(TargetCharacter);
				continue;
			}
		}
	}

	return FoundTargets.Num() > 0;
}

bool AMiniCyphersProjectile::TryGetOverlapTarget(AMiniCyphersCharacter* Character, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(Character, Targets))
	{
		FoundTarget = Targets[0];
	}

	return FoundTarget != nullptr;
}

// Called every frame
void AMiniCyphersProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiniCyphersProjectile::Initialize(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character;
}

void AMiniCyphersProjectile::SetDirection(FVector Direction)
{
	ProjectileDirection = Direction;
}

