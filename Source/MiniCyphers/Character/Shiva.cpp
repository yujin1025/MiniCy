// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiva.h"
#include "Projectile/ShivaNormalAttackProjectile.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"

AShiva::AShiva()
{
	NormalAttackProjectileStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("NormalAttackProjctileStartLocation"));
	NormalAttackProjectileStartLocation->SetupAttachment(GetRootComponent());
	NormalAttackProjectileStartLocation->SetRelativeLocation(FVector(10.0f, 48.4f, 10.0f));

	SkillRange = 200.0f;
	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> SHIVA_DEAD (TEXT("/Script/Engine.AnimMontage'/Game/Assets/BluePrints/Animation/Montage/Shiva/DeathMontage.DeathMontage'"));

	if (SHIVA_DEAD.Succeeded())
	{
		DeathMontage = SHIVA_DEAD.Object;
	}*/

}

bool AShiva::IsSatisfiedNormalAttack()
{
	return Super::IsSatisfiedNormalAttack();
}

bool AShiva::IsSatisfiedRightClickAttack()
{
	return Super::IsSatisfiedRightClickAttack();
}

bool AShiva::IsSatisfiedShiftAttack()
{
	return Super::IsSatisfiedShiftAttack();
}

bool AShiva::IsSatisfiedQSkill()
{
	return Super::IsSatisfiedQSkill();
}

bool AShiva::IsSatisfiedUltimateSkill()
{
	return true;
}

bool AShiva::IsSatisfiedGrabSkill()
{
	return true;
}

void AShiva::OnUseNormalAttack()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = ((NormalAttackProjectileStartLocation != nullptr) ? NormalAttackProjectileStartLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
			if (NormalAttackProjectileStartLocation == nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("Shiva NA Projectlie Start Location NULL"));
				return;
			}
			const FVector SpawnLocation = NormalAttackProjectileStartLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			// spawn the projectile at the muzzle
			auto tempActor = World->SpawnActor<AShivaNormalAttackProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (tempActor == nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("tempActor NULL"));
				return;
			}
			tempActor->SetCharacterController(GetController());
			tempActor->SetProjectileOwner(this);

		}
	}
	else
		UE_LOG(LogTemp, Log, TEXT("ProjectileClass NULL"))
}

void AShiva::OnUseRightClickAttack()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		ACharacter* HitCharacter = nullptr;
		const FVector TraceStart = GetActorLocation();
		const FVector TraceEnd = TraceStart + GetActorForwardVector() * SkillRange;

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // 캐릭터 자신은 무시

		// 레이 캐스트를 통해 캐릭터의 사정거리 안에 몬스터가 있는지 확인
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Pawn, CollisionParams))
		{
			HitCharacter = Cast<ACharacter>(HitResult.GetActor());
		}

		if (HitCharacter)
		{
			UHealthComponent* DamagedHealthComponent = HitCharacter->FindComponentByClass<UHealthComponent>();

			if (DamagedHealthComponent)
			{
				DamagedHealthComponent->ChangeHealth(this, -10); 
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Target"));
		}
	}
}

void AShiva::OnUseShiftLeftClickAttack()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		bInvincible = true;

		float TargetHeight = HitResult.ImpactPoint.Z;
		FVector NewLocation = FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, TargetHeight);

		SetActorLocation(NewLocation);

		DrawDebugSphere(GetWorld(), NewLocation, 10.0f, 12, FColor::Green, false, 5.0f); //마우스 클릭한 곳 디버그


		ACharacter* HitCharacter = nullptr;
		const FVector TraceStart = GetActorLocation();
		const FVector TraceEnd = NewLocation;
		FHitResult HitResultAfterTeleport;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); 

		// 레이 캐스트를 통해 순간이동 후 목표 지점에 적이 있는지 확인
		if (GetWorld()->LineTraceSingleByChannel(HitResultAfterTeleport, TraceStart, TraceEnd, ECC_Pawn, CollisionParams))
		{
			HitCharacter = Cast<ACharacter>(HitResultAfterTeleport.GetActor());
		}

		if (HitCharacter)
		{
			UHealthComponent* DamagedHealthComponent = HitCharacter->FindComponentByClass<UHealthComponent>();

			if (DamagedHealthComponent)
			{
				// 킬 힐을 맞은 적은 넘어짐 (띄우는 힘이 0인 에어본 타격) 아직 구현안함
				DamagedHealthComponent->ChangeHealth(this, -10);
				DrawDebugString(GetWorld(), TraceEnd, FString::Printf(TEXT("10")), nullptr, FColor::Red, 3.0f, false);
			}
		}

		bInvincible = false;
	}
}

void AShiva::OnUseQSkill()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	TArray<FHitResult> HitResults;
	FVector StartLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLocation = StartLocation + ForwardVector * SkillRange;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// 레이 캐스트를 통해 사정거리 안의 모든 적을 확인
	if (GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, ECC_Pawn, CollisionParams))
	{
		for (const FHitResult& HitResult : HitResults)
		{
			ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());
			if (HitCharacter)
			{
				UHealthComponent* DamagedHealthComponent = HitCharacter->FindComponentByClass<UHealthComponent>();
				if (DamagedHealthComponent)
				{
					DamagedHealthComponent->ChangeHealth(this, -10);
					break; // 1마리만 타격
				}
			}
		}
	}
}

void AShiva::OnUseUltimateSkill()
{
}

void AShiva::OnUseGrabSkill()
{
}

void AShiva::OnDie()
{
	Super::OnDie();
}
