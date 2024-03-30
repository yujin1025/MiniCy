// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/MiniCyphersCharacter.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifyAttackState.generated.h"

class AMiniCyphersCharacter;

UENUM()
enum class EDetectType
{
	Sphere = 0,
	Box = 1,
};

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyAttackState : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyAttackState();

	void TryAttack(USkeletalMeshComponent* MeshComp);
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FCollisionShape MakeDetection(UWorld* World, FVector Center, FQuat Quat, FColor Color, const float X, const float Y, const float Z);

	bool TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets);

private:
	TMap<int, int> attackedCountsByCharacter;

protected:
	UPROPERTY(Editanywhere)
	EDetectType DetectType = EDetectType::Sphere;

	UPROPERTY(EditAnywhere)
	int MaxAttackCount = 1;

	UPROPERTY(EditAnywhere)
	int MaxAttackCountByEnemy = 1;

	int CurrentAttackCount = 0;

	UPROPERTY(EditAnywhere)
	int DamageAmount;

	UPROPERTY(EditAnywhere)
	float DetectX = 600.0f;
	
	UPROPERTY(EditAnywhere)
	float DetectY = 800.0f;

	UPROPERTY(EditAnywhere)
	float DetectZ = 800.0f;

	UPROPERTY(EditAnyWhere)
	FVector CenterOffset;

	UPROPERTY(EditAnywhere)
	float KnockBackDistance = 50.0f;

	UPROPERTY(EditAnywhere)
	float UpperVelocity = 100.0f;

	UPROPERTY(EditAnywhere)
	bool IsMelee = false;

	UPROPERTY(EditAnywhere)
	float StiffTime = 5.0f;

	UPROPERTY(EditAnywhere)
	EDamageType DamageType = EDamageType::Stand;

};
