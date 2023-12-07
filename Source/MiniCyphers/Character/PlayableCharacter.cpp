// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
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

APlayableCharacter::APlayableCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AIControllerClass = nullptr;
	AutoPossessAI = EAutoPossessAI::Disabled;

	isShift = false;
}


void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayableCharacter::OnMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayableCharacter::OnLook);

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::NormalAttack], ETriggerEvent::Triggered, this, &APlayableCharacter::OnNormalAttack);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::RightClickAttack], ETriggerEvent::Triggered, this, &APlayableCharacter::OnRightClickAttack);

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::ShiftAttack], ETriggerEvent::Started, this, &APlayableCharacter::OnShift);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::ShiftAttack], ETriggerEvent::Completed, this, &APlayableCharacter::OnShiftEnd);

		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::QSkillAttack], ETriggerEvent::Triggered, this, &APlayableCharacter::OnQSkill);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::UltimateAttack], ETriggerEvent::Triggered, this, &APlayableCharacter::OnUltimateSkill);
		EnhancedInputComponent->BindAction(InputActionMap[EAttackType::GrabSkillAttack], ETriggerEvent::Triggered, this, &APlayableCharacter::OnGrabSkill);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayableCharacter::BeginPlay()
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


void APlayableCharacter::OnMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	Move(MovementVector);
}

void APlayableCharacter::OnLook(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	Look(LookAxisVector);
}

void APlayableCharacter::OnNormalAttack(const FInputActionValue& Value)
{
	if (IsSatisfiedNormalAttack() == false)
		return;

	UseSkill(isShift ? EAttackType::ShiftAttack : EAttackType::NormalAttack);
}

void APlayableCharacter::OnRightClickAttack(const FInputActionValue& Value)
{
	if (IsSatisfiedRightClickAttack() == false)
		return;

	UseSkill(EAttackType::RightClickAttack);
}

void APlayableCharacter::OnQSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedQSkill() == false)
		return;

	UseSkill(EAttackType::QSkillAttack);
}

void APlayableCharacter::OnUltimateSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedUltimateSkill() == false)
		return;

	UseSkill(EAttackType::UltimateAttack);
}

void APlayableCharacter::OnGrabSkill(const FInputActionValue& Value)
{
	if (IsSatisfiedGrabSkill() == false)
		return;

	UseSkill(EAttackType::GrabSkillAttack);
}