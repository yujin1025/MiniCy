// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MiniCyphersCharacter.generated.h"

class UHealthComponent;
class UComboActionComponent;
class USoundComponent;
class URandomMotionComponent;
class UQuestComponent;
class UHitDeadComponent;

// Stand와 PowerKnockBack의 차이는 모션 뿐
UENUM()
enum class EDamageType
{
	None = -1,
	Stand = 0,
	Airborne = 1,
	PowerKnockBack = 2,
};

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

public:
	void Move(const FVector2D Value);
	virtual void Look(const FVector2D Value);

protected:
	bool CheckCoolTime(EAttackType AttackType);

	FString GetEnumNameAsString(EAttackType EnumValue);

	virtual void BeginPlay() override;
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

	virtual void OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee);
	virtual void OnDie();
	
public:
	bool TryGetOverlapResult(AMiniCyphersCharacter* Character, TArray<FOverlapResult>& OverlapResults);

	bool TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Character, OUT AMiniCyphersCharacter*& FoundTarget);

public:
	bool IsPlayer(); //플레이어인지 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	bool IsPlayerTeam = false;

	UPROPERTY(EditAnywhere)
	float KnockBackSpeedRate = 5.0f;

	UPROPERTY(EditAnywhere)
	float SuperArmorStiffRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float SuperArmorKnockBackPowerRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float TargetDetectRadius = 1000.0f;

	UPROPERTY(EditAnywhere)
	FColor DetectTargetDebugColor = FColor::Red;

	bool bSuperArmor = false;
	bool bInvincible = false;
	bool IsDead = false;

	EAttackType ProgressingAttackType = EAttackType::Max;

	FVector KnockBackDirection = FVector::ZeroVector;
	float RemainStiffTime = 0.0f;
	float RemainKnockBackPower = 0.0f;


public:
	FVector GetLookVector(AMiniCyphersCharacter*& Target) const;

	void RotateToTarget(AMiniCyphersCharacter*& Target, float RotationSpeed);
	void SetRotation(FRotator Rotation, float RotationSpeed);

	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget);

	virtual FVector GetTargetPosition();
	virtual FVector GetMyLocation() const;
	virtual AMiniCyphersCharacter* GetTarget();
};

