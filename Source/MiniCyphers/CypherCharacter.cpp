// Fill out your copyright notice in the Description page of Project Settings.


#include "CypherCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ComboActionComponent.h"
#include "HealthComponent.h"

ACypherCharacter::ACypherCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	ActionComponentMap.Empty();
	for (int i = 0; i < (int)EAttackType::Max; i++)
	{
		auto AttackType = (EAttackType)i;

		FString AttackTypeStr = GetEnumNameAsString(AttackType);
		FString ComponentName = TEXT("ComboActionComponent [") + AttackTypeStr + "]";
		auto Component = CreateDefaultSubobject<UComboActionComponent>((FName)*ComponentName);
		ActionComponentMap.Add(AttackType, Component);
	}
}


void ACypherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::NormalAttack], ETriggerEvent::Triggered, this, &ACypherCharacter::OnNormalAttack);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::RightClickAttack], ETriggerEvent::Triggered, this, &ACypherCharacter::OnRightClickAttack);

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::ShiftAttack], ETriggerEvent::Started, this, &ACypherCharacter::OnShift);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::ShiftAttack], ETriggerEvent::Completed, this, &ACypherCharacter::OnShiftEnd);

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::QSkillAttack], ETriggerEvent::Triggered, this, &ACypherCharacter::OnQSkill);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::UltimateAttack], ETriggerEvent::Triggered, this, &ACypherCharacter::OnUltimateSkill);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::GrabSkillAttack], ETriggerEvent::Triggered, this, &ACypherCharacter::OnGrabSkill);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACypherCharacter::OnNormalAttack(const FInputActionValue& Value)
{
	if (IsSatisfiedNormalAttack() == false)
		return;

	UseSkill(isShift ? EAttackType::ShiftAttack : EAttackType::NormalAttack);
}

void ACypherCharacter::OnRightClickAttack(const FInputActionValue& Value)
{
	if (IsSatisfiedRightClickAttack() == false)
		return;

	UseSkill(EAttackType::RightClickAttack);
}

void ACypherCharacter::OnQSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedQSkill() == false)
		return;

	UseSkill(EAttackType::QSkillAttack);
}

void ACypherCharacter::OnUltimateSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedUltimateSkill() == false)
		return;

	UseSkill(EAttackType::UltimateAttack);
}

void ACypherCharacter::OnGrabSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedGrabSkill() == false)
		return;

	UseSkill(EAttackType::GrabSkillAttack);
}

void ACypherCharacter::UseSkill(EAttackType AttackType)
{
	if (ActionComponentMap.Contains(AttackType) == false)
		return;

	for (auto& MapPair : ActionComponentMap)
	{
		if (MapPair.Key == AttackType)
			continue;

		MapPair.Value->ResetCombo();
	}

	ActionComponentMap[AttackType]->DoCombo();

	switch (AttackType)
	{
	case EAttackType::NormalAttack:
		OnUseNormalAttack();
		break;

	case EAttackType::RightClickAttack:
		OnUseRightClickAttack();
		break;

	case EAttackType::ShiftAttack:
		OnUseShiftLeftClickAttack();
		break;

	case EAttackType::QSkillAttack:
		OnUseQSkill();
		break;

	case EAttackType::UltimateAttack:
		OnUseUltimateSkill();
		break;

	case EAttackType::GrabSkillAttack:
		OnUseGrabSkill();
		break;
	}
}
