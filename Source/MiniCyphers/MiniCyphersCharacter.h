// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MiniCyphersCharacter.generated.h"

class UHealthComponent;
class UComboActionComponent;

UENUM()
enum class EAttackType
{
	NormalAttack,
	RightClickAttack,
	ShiftAttack,
	QSkillAttack,
	UltimateAttack,
	GrabSkillAttack,
	Max,
};


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

	UHealthComponent* HealthComponent;

protected:
	void Move(const FVector2D Value);
	void Look(const FVector2D Value);

	FString GetEnumNameAsString(EAttackType EnumValue);

public:
	void UseSkill(EAttackType AttackType);

	virtual bool IsSatisfiedNormalAttack() { return true; }
	virtual bool IsSatisfiedRightClickAttack() { return true; }
	virtual bool IsSatisfiedQSkill() { return true; }
	virtual bool IsSatisfiedUltimateSkill() { return true; }
	virtual bool IsSatisfiedGrabSkill() { return true; }
	virtual bool IsSatisfiedShiftAttack() { return true; }

	virtual void OnUseNormalAttack() {}
	virtual void OnUseShiftLeftClickAttack() {}
	virtual void OnUseRightClickAttack() {}
	virtual void OnUseQSkill() {}
	virtual void OnUseUltimateSkill() {}
	virtual void OnUseGrabSkill() {}
};

