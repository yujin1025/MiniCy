// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniCyphersCharacter.h"
#include "CypherCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UComboActionComponent;
struct FInputActionValue;
class UHealthComponent;

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

/**
 * 
 */
UCLASS(ABSTRACT)
class MINICYPHERS_API ACypherCharacter : public AMiniCyphersCharacter
{
	GENERATED_BODY()

		// ¿Œ«≤
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TMap<EAttackType, UInputAction*> InputActionMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
		TMap<EAttackType, UComboActionComponent*> ActionComponentMap;

	UHealthComponent* HealthComponent;
	bool isShift = false;

public:
	ACypherCharacter();

private:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	void OnNormalAttack(const FInputActionValue& Value);
	void OnRightClickAttack(const FInputActionValue& Value);

	void OnShift(const FInputActionValue& Value) { isShift = true; }
	void OnShiftEnd(const FInputActionValue& Value) { isShift = false; }

	void OnQSkill(const FInputActionValue& Value);

	void OnUltimateSkill(const FInputActionValue& Value);
	void OnGrabSkill(const FInputActionValue& Value);
	
	void UseSkill(EAttackType AttackType);

	FString GetEnumNameAsString(EAttackType EnumValue)
	{
		switch (EnumValue)
		{
		case EAttackType::NormalAttack:
			return "NormalAttack";

		case EAttackType::RightClickAttack:
			return "RightAttack";

		case EAttackType::ShiftAttack:
			return "ShiftAttack";

		case EAttackType::QSkillAttack:
			return "QSkillAttack";

		case EAttackType::UltimateAttack:
			return "UltimateAttack";

		case EAttackType::GrabSkillAttack:
			return "GrabSkillAttack";
		}

		return "";
	}

protected:
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
