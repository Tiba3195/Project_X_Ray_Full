// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FPSProjectile.h"
#include "ProjectileFireControlComponent.generated.h"

UENUM(BlueprintType)
enum class FireMode : uint8 {
	AlphaBurst,
	Alternate
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_X_RAY_API UProjectileFireControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileFireControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		FireMode mode = FireMode::AlphaBurst;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire(UArrowComponent* Muzzle, AActor* Owner,bool IsBot);



	void Fire(TArray<UArrowComponent*> Muzzle, AActor* Owner, bool IsBot);
	void Fire(TArray<UArrowComponent*> Muzzle, AActor* Owner, bool IsBot, FRotator direction);
	int32 currentmuzzle = 0;
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;
};
