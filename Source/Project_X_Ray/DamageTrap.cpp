//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#include "Project_X_Ray.h"
#include "DamageTrap.h"
#include "BaseCharacter.h"


void ADamageTrap::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	ABaseCharacter* found = Cast<ABaseCharacter>(OtherActor);
	if (found != nullptr)
	{
		if (found->bCanBeDamaged)
		{
			if (DamageEffect != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, DamageEffect, GetActorLocation() + FVector(0.0f, 0.0f, EffectHeightOffset), GetActorRotation(), true);
			}
			FRadialDamageEvent DamageType = FRadialDamageEvent();
			DamageType.Params.BaseDamage = Damage;
			DamageType.Params.DamageFalloff = DamageFalloff;
			DamageType.Params.MinimumDamage = MinimumDamage;
			DamageType.Params.OuterRadius = OuterRadius;
			DamageType.Origin = found->GetActorLocation();
			//DamageType.DamageTypeClass
			found->TakeDamage(Damage, DamageType, nullptr, this);
		}
	}

}

