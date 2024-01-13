// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaNormalAttackProjectile.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShivaNormalAttackProjectile::AShivaNormalAttackProjectile()
{

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShivaNormalAttackProjectile::OnAttack);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp;
	ProjectileMovementComp->InitialSpeed = 5000.f;
	ProjectileMovementComp->MaxSpeed = 5000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

	// Die after 1 seconds by default
	InitialLifeSpan = 3.0f;

}

void AShivaNormalAttackProjectile::BeginPlay()
{
	Super::BeginPlay();	
	//InitVelocity()
}

void AShivaNormalAttackProjectile::Tick(float DeltaTime)
{

}

// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
void AShivaNormalAttackProjectile::InitVelocity(const FVector& ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection * ProjectileMovementComp->InitialSpeed;
}

void AShivaNormalAttackProjectile::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMiniCyphersCharacter* DamagedCharacter = Cast<AMiniCyphersCharacter>(OtherActor); //투사체에 맞은 놈
	if ((OtherComp != nullptr) && DamagedCharacter != nullptr)
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation()); //충격 추가하는 코드인데 지금은 필요 없어서 일단 비활성화 해둠

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
							
			DamagedCharacter->OnHit(ProjectileOwner); //이건 쳐맞은 애 애니메이션 재생용

			UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent == nullptr)
				return;

			DamagedHealthComponent->ChangeHealth(-10, false);
			UE_LOG(LogTemp, Warning, TEXT("NonPlayer's current health: %d"), DamagedHealthComponent->GetCurrentHealth());


			// 총을 쏨 > 총알이 어딘가에 맞았음(안사라지고) > 맞은 물체를 가져와서 > 맞은 물체가 떄릴수있는애면 > 데미지를 줘 
			// OnFire > OnHit > HitResult.GetActor > if(Damagable) > HitResult의 TakeDamage 호출

		}
	}
}


AController* AShivaNormalAttackProjectile::SetCharacterController(AController* Controller)
{
	CharacterController = Controller;
	return CharacterController;
}

void AShivaNormalAttackProjectile::SetProjectileOwner(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character; //때린놈
}
