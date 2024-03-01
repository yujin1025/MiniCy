// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersService.h"
#include "BTService_Detect.generated.h"

class UBehaviorTreeComponent;
class UMiniCyphersService;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTService_Detect : public UMiniCyphersService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void FindTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* MyCharacter, OUT AMiniCyphersCharacter*& DetectedTarget);
	bool TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget);
	void SetDetectedTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* TargetCharacter);
	bool TryGetAttackerTrackingResult(UBehaviorTreeComponent& OwnerComp, OUT AMiniCyphersCharacter*& FoundTarget);

	void OnTickNode(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);

private:
	UPROPERTY(EditAnywhere)
	bool IsPlayerDetect = true;

	UPROPERTY(EditAnywhere)
	float DetectRadius = 600.0f;
};
