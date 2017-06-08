//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileFireControlComponent.h"
#include "PlayerWeapon.generated.h"





UCLASS(BlueprintType)
class PROJECT_X_RAY_API APlayerWeapon : public AActor
{
	GENERATED_BODY()	


public:	
	// Sets default values for this actor's properties
	APlayerWeapon();
	APlayerWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate = 3;

	float CurrentFireRate = 0;

	// Function that handles firing projectiles.
	UFUNCTION()
	void Fire(AActor* sender, bool IsBot);

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	int PlayerID = 0;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UProjectileFireControlComponent* ProjectileFireControlComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	USkeletalMeshComponent* FP_Gun;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UArrowComponent* MuzzleOffset;

	float Age = 0;
	UPROPERTY(EditAnywhere, Category = Projectile)
		float MaxMuzzleFlashAge = 0.06;

	
	
};
