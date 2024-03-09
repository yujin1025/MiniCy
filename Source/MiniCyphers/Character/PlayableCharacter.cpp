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
#include "../MiniCyphersPlayerController.h"
#include "../MiniCyphersPlayerState.h"
#include "ItemActionComponent.h"
#include "InputBlockComponent.h"

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

	ItemActionComponent = CreateDefaultSubobject<UItemActionComponent>(TEXT("ItemActionComponent"));
	InputBlockComponent = CreateDefaultSubobject<UInputBlockComponent>(TEXT("InputBlockComponent"));
	
	AIControllerClass = nullptr;
	AutoPossessAI = EAutoPossessAI::Disabled;

	isShift = false;
}


void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

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

void APlayableCharacter::OnMove(const FInputActionValue& Value)
{
	if (InputBlockComponent->bInputBlock)
		return;

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	Move(MovementVector);
	OnMoveDelegate.Broadcast(MovementVector);
}

void APlayableCharacter::OnLook(const FInputActionValue& Value)
{
	if (InputBlockComponent->bInputBlock)
		return;

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	Look(LookAxisVector);
}

void APlayableCharacter::Look(const FVector2D Value)
{
	Super::Look(Value);

	FRotator Rotation = Controller->GetControlRotation();
	float CurrentRotation = Rotation.Pitch > 270.0f ? Rotation.Pitch - 360.0f : Rotation.Pitch;
	Rotation.Pitch = FMath::Clamp(CurrentRotation, CameraPitchDownLock, CameraPitchUpLock);
	Controller->SetControlRotation(Rotation);
}

AMiniCyphersPlayerState* APlayableCharacter::GetState()
{
	return Cast<AMiniCyphersPlayerState>(GetPlayerState());
}

AMiniCyphersPlayerController* APlayableCharacter::GetPlayerController()
{
	return Cast<AMiniCyphersPlayerController>(Controller);
}

// 플레이어의 타겟 포지션은 AMiniCyphersCharacter가 아닐 수도 있다.
// 플레이어의 타겟은 항상 다르므로, 항상 nullptr이다.
FVector APlayableCharacter::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget)
{
	FVector CameraLocation;
	FRotator CameraRotation;

	if (Controller)
	{
		Controller->GetPlayerViewPoint(CameraLocation, CameraRotation); // 플레이어의 시점을 가져옵니다.
	}

	FVector Start = CameraLocation; // 레이의 시작점은 카메라 위치입니다.
	FVector End = Start + (CameraRotation.Vector() * RayCastDistance); // 레이의 끝점은 카메라의 방향을 따라서 RaycastLength만큼 떨어진 지점입니다.

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 레이를 쏠 때 플레이어 캐릭터는 무시합니다.
	// 레이캐스트를 수행합니다.
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, Channel, CollisionParams))
	{
		IsFoundTarget = true;
		return FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
	}

	IsFoundTarget = false;
	return End;
}

bool APlayableCharacter::IsSatisfiedNormalAttack()
{
	return Super::IsSatisfiedNormalAttack() && !InputBlockComponent->bInputBlock;
}

bool APlayableCharacter::IsSatisfiedRightClickAttack()
{
	return Super::IsSatisfiedRightClickAttack() && !InputBlockComponent->bInputBlock;
}

bool APlayableCharacter::IsSatisfiedQSkill()
{
	return Super::IsSatisfiedQSkill() && !InputBlockComponent->bInputBlock;
}

bool APlayableCharacter::IsSatisfiedShiftAttack()
{
	return Super::IsSatisfiedShiftAttack() && !InputBlockComponent->bInputBlock;
}


void APlayableCharacter::OnNormalAttack(const FInputActionValue& Value)
{
	if (isShift)
	{
		if (IsSatisfiedShiftAttack())
		{
			UseSkill(EAttackType::ShiftAttack);
		}
	}
	else
	{
		if (IsSatisfiedNormalAttack())
		{
			UseSkill(EAttackType::NormalAttack);
			OnAttackDelegate.Broadcast();
		}
	}

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