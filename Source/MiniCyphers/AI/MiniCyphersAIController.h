// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MiniCyphersAIController.generated.h"

/**
 * 블루 프린트로 파생 컨트롤러를 만듬
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMiniCyphersAIController();
	
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetObjectKey;
	static const FName DamagedCountKey;
	static const FName DamagedTypeKey;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	void SetCharacterPerception(AMiniCyphersCharacter* InChar);

	UFUNCTION()
	void OnDamaged(AMiniCyphersCharacter* Attacker, float Amount, bool isMelee);


private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset;
	
	UPROPERTY(EditAnywhere)
	class UBlackboardData* BBAsset;

	UPROPERTY(EditAnywhere)
	float AttackerTrackingTime = 4.0f;
};
