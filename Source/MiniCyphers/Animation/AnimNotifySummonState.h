// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifySummonState.generated.h"

UENUM()
enum class ESummonType
{
	None = -1,
	ShivaKnife = 0, // 시바 평타 나이프
	TowerShot = 1, // 타워 포탄
	TrooperStone = 2, // 투루퍼 전방 스킬 돌
};

class AMiniCyphersCharacter;
class AShiva;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifySummonState : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()
	
private:
	void SummonObject(AMiniCyphersCharacter* Character);
	void SummonShivaKnife(AShiva* ShivaCharacter);

	UPROPERTY(EditAnywhere)
	ESummonType SummonType;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMiniCyphersProjectile> ProjectileClass;

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

};
