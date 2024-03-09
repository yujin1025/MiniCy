// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersProjectile.h"
#include "ShivaShadowKnife.generated.h"


class AMiniCyphersCharacter;

UCLASS()
class MINICYPHERS_API AShivaShadowKnife : public AMiniCyphersProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShivaShadowKnife();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere)
	float AttackRange = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
	void OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Initialize(AMiniCyphersCharacter* Character);
	void SetDirection(FVector Direction);

private:
	AMiniCyphersCharacter* ProjectileOwner;
	FVector ProjectileDirection;

	float CurrentDeltaTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float StiffTime = 5.0f;

	UPROPERTY(EditAnywhere)
	int DamageAmount = 5;

	UPROPERTY(EditAnywhere)
	float KnockBackDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	UParticleSystem* EnemyHitParticleEffect;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	UParticleSystem* WallHitParticleEffect;

	UPROPERTY(EditAnywhere)
	float ParticleScale = 1.0f;

	UPROPERTY(EditAnywhere)
	float LifeSeconds = 1.5f;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 2000.0f;
};
