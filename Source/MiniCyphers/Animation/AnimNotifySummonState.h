// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifySummonState.generated.h"

UENUM()
enum class ESummonType
{
	None = -1,
	ShivaKnife = 0, // ½Ã¹Ù ÆòÅ¸ ³ªÀÌÇÁ
	TrooperStone = 1, // Åõ·çÆÛ Àü¹æ ½ºÅ³ µ¹
	BombSentinel = 2, // ÆøÅº ¼¾Æ¼³Ú
	BombSentinelBomb = 3, // ÆøÅº ¼¾Æ¼³ÚÀÇ ½ÇÁ¦ Æø¹ß
};

class AMiniCyphersCharacter;
class AShiva;
class ATrooper;
class ABombSentinel;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifySummonState : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()
	
private:
	void SummonObject(AMiniCyphersCharacter* Character);
	void SummonTrooperStone(ATrooper* TrooperCharacter);
	void SummonShivaKnife(AShiva* ShivaCharacter);
	void SummonBombSentinel(ATrooper* TrooperCharacter);
	void SummonBombSentinelBomb(ABombSentinel* BombSentinel);

	UPROPERTY(EditAnywhere)
	ESummonType SummonType;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMiniCyphersProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMiniCyphersCharacter> SummonCharacterClass;

	UPROPERTY(EditAnywhere)
	TArray<FVector> TrooperSummonOffsetArray;

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

};
