// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MiniCyphersCharacter.generated.h"

class UHealthComponent;
class UComboActionComponent;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NormalAttack,
	RightClickAttack,
	ShiftAttack,
	QSkillAttack,
	UltimateAttack,
	GrabSkillAttack,
	Max,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUseSkill, EAttackType)
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMiniCyphersCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMiniCyphersCharacter();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<EAttackType, UComboActionComponent*> ActionComponentMap;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Id, meta = (AllowPrivateAccess = "true"))
	int CharacterId;

	UHealthComponent* HealthComponent;

protected:
	void Move(const FVector2D Value);
	void Look(const FVector2D Value);

	FString GetEnumNameAsString(EAttackType EnumValue);

public:
	void UseSkill(EAttackType AttackType);
	void OnFinishedSkillMotion(EAttackType AttackType);

	FOnUseSkill OnUseSkillDelegate;

public:
	bool bCanAttack = true;

	virtual bool IsSatisfiedNormalAttack();
	virtual bool IsSatisfiedRightClickAttack();
	virtual bool IsSatisfiedQSkill();
	virtual bool IsSatisfiedUltimateSkill() { return true; }
	virtual bool IsSatisfiedGrabSkill() { return true; }
	virtual bool IsSatisfiedShiftAttack();

	virtual void OnUseNormalAttack() {}
	virtual void OnUseShiftLeftClickAttack() {}
	virtual void OnUseRightClickAttack() {}
	virtual void OnUseQSkill() {}
	virtual void OnUseUltimateSkill() {}
	virtual void OnUseGrabSkill() {}

	virtual void OnHit(AMiniCyphersCharacter* Attacker);
	virtual void OnDie();


public:
	bool IsPlayer(); //플레이어인지 여부

	FVector GetLookVector(AMiniCyphersCharacter*& Target) const;

	void RotateToTarget(AMiniCyphersCharacter*& Target, float RotationSpeed);
	void SetRotation(FRotator Rotation, float RotationSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* NormalEffectsSentinel;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* NormalEffectsTrooper;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* CriticalEffectsSentinel;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* CriticalEffectsTrooper;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* NormalAttackSentinel;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* NormalAttackTrooper;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* CriticalAttackSentinel;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* CriticalAttackTrooper;
};

