// Fill out your copyright notice in the Description page of Project Settings.


#include "CypherCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ComboActionComponent.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

ACypherCharacter::ACypherCharacter()
{
	isShift = false;

	ActionComponentMap.Empty();
	for (int i = 0; i < (int)EAttackType::Max; i++)
	{
		auto AttackType = (EAttackType)i;

		FString AttackTypeStr = GetEnumNameAsString(AttackType);
		FString ComponentName = TEXT("ComboActionComponent [") + AttackTypeStr + "]";
		auto Component = CreateDefaultSubobject<UComboActionComponent>((FName)*ComponentName);
		ActionComponentMap.Add(AttackType, Component);
	}

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}


void ACypherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACypherCharacter::OnMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACypherCharacter::OnLook);

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

void ACypherCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


void ACypherCharacter::OnMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	Move(MovementVector);
}

void ACypherCharacter::OnLook(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	Look(LookAxisVector);
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

	Super::UseSkill(AttackType);
}
