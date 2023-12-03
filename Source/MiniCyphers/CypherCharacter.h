// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniCyphersCharacter.h"
#include "CypherCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UComboActionComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	bool isShift = false;

public:
	ACypherCharacter();

private:
	void OnNormalAttack(const FInputActionValue& Value);
	void OnRightClickAttack(const FInputActionValue& Value);

	void OnShift(const FInputActionValue& Value) { isShift = true; }
	void OnShiftEnd(const FInputActionValue& Value) { isShift = false; }

	void OnQSkill(const FInputActionValue& Value);

	void OnUltimateSkill(const FInputActionValue& Value);
	void OnGrabSkill(const FInputActionValue& Value);

	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);

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

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
};
