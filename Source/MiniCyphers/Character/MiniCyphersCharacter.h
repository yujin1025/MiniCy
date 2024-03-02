// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Animation/AnimNotifyAttackState.h"
#include "Logging/LogMacros.h"
#include "MiniCyphersCharacter.generated.h"

class UHealthComponent;
class UComboActionComponent;
class USoundComponent;
class URandomMotionComponent;
class UQuestComponent;
class UHitDeadComponent;

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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMove, FVector2D)
DECLARE_MULTICAST_DELEGATE(FOnAttack)


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<EAttackType, float> ActionCoolTimeMap;

	TMap<EAttackType, float> CurrentActionCoolTimeMap;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Id, meta = (AllowPrivateAccess = "true"))
	int CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	URandomMotionComponent* RandomMotionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	UHitDeadComponent* HitDeadComponent;

	UHealthComponent* HealthComponent;
	UQuestComponent* QuestComponent;

protected:
	void Move(const FVector2D Value);
	virtual void Look(const FVector2D Value);

	bool CheckCoolTime(EAttackType AttackType);

	FString GetEnumNameAsString(EAttackType EnumValue);
	virtual void Tick(float DeltaTime) override;

public:
	void UseSkill(EAttackType AttackType);
	void OnFinishedSkillMotion(EAttackType AttackType);

	FOnUseSkill OnUseSkillDelegate;
	FOnMove OnMoveDelegate;
	FOnAttack OnAttackDelegate;

private:
	float CurrentDeltaTime = 0.0f;

public:
	virtual bool IsSatisfiedNormalAttack();
	virtual bool IsSatisfiedRightClickAttack();
	virtual bool IsSatisfiedQSkill();
	virtual bool IsSatisfiedUltimateSkill();
	virtual bool IsSatisfiedGrabSkill();
	virtual bool IsSatisfiedShiftAttack();

	virtual void OnUseNormalAttack();
	virtual void OnUseShiftLeftClickAttack() {}
	virtual void OnUseRightClickAttack() {}
	virtual void OnUseQSkill() {}
	virtual void OnUseUltimateSkill() {}
	virtual void OnUseGrabSkill() {}

	virtual void OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee);
	virtual void OnDie();
	
protected:
	bool TryGetOverlapResult(AMiniCyphersCharacter* Character, TArray<FOverlapResult>& OverlapResults);

	bool TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Character, OUT AMiniCyphersCharacter*& FoundTarget);

	void SetAnimationSpeedRate(float Rate);
public:
	bool IsPlayer(); //플레이어인지 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	bool isPlayerTeam = false;

	bool bInvincible = false;
	bool bSuperArmor = false;
	bool isProgressingSkillMotion = false;
	bool isDead = false;

	float DetectRadius = 1000.0f;

	FVector GetLookVector(AMiniCyphersCharacter*& Target) const;

	void RotateToTarget(AMiniCyphersCharacter*& Target, float RotationSpeed);
	void SetRotation(FRotator Rotation, float RotationSpeed);

	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget);
};

