// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

UCLASS()
class PROJECT_X_RAY_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();
	void RegisterDelegate();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float MaxAge=0;
	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(BlueprintReadOnly, Category = Mesh)
		UArrowComponent* MuzzleOffset;


	UFUNCTION()
	// Function that is called when the projectile hits something.
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = Projectile)
	UParticleSystem* ImpactFX;

	UPROPERTY(EditAnywhere, Category = Projectile)
		UParticleSystemComponent* TrailFX;


	UPROPERTY(EditAnywhere, Category = Projectile)
		float Damage = 100.0f;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float DamageFalloff = 750;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float MinimumDamage = 350;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float OuterRadius = 200;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float WeaponRange = 2000;
	UPROPERTY(EditAnywhere, Category = Projectile)
		bool InstantHit = false;


	

};

