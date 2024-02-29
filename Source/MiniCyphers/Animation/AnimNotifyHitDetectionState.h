// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyHitDetectionState.generated.h"

class UHealthComponent;
class AMiniCyphersCharacter;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyHitDetectionState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyHitDetectionState();

	void HitDetection(USkeletalMeshComponent* MeshComp);
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FCollisionShape MakeDetection(const float SphereRadius, const float Long);

	AMiniCyphersCharacter* GetCharacter(const FOverlapResult& OverlapResult);

	UHealthComponent* GetHealthComponent(USkeletalMeshComponent* MeshComp);
	bool TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget);

protected:

	UPROPERTY(EditAnywhere)
	int MaxAttackCount = 1;

	int CurrentAttackCount = 0;

	UPROPERTY(EditAnywhere)
	int DamageAmount;

	UPROPERTY(EditAnywhere)
	float DetectShort = 600.0f;
	
	UPROPERTY(EditAnywhere)
	float DetectLong = 800.0f;
};
