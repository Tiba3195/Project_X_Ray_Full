//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#pragma once

#include "BaseTrapActor.h"
#include "DamageTrap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ADamageTrap : public ABaseTrapActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		virtual	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	UPROPERTY(EditAnywhere, Category = Trap)
		float Damage = 100.0f;
	UPROPERTY(EditAnywhere, Category = Trap)
		float DamageFalloff = 750;
	UPROPERTY(EditAnywhere, Category = Trap)
		float MinimumDamage = 350;
	UPROPERTY(EditAnywhere, Category = Trap)
		float OuterRadius = 200;

	UPROPERTY(EditAnywhere, Category = Trap)
		UParticleSystem* DamageEffect;
};
