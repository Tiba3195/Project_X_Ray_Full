//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#include "Project_X_Ray.h"
#include "SnareTrap.h"
#include "BaseCharacter.h"

void ASnareTrap::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	ABaseCharacter* found = Cast<ABaseCharacter>(OtherActor);
	if (found != nullptr)
	{
		SpeedModifier = FMath::Clamp(SpeedModifier, 1.0f, 10.0f);
		found->GetCharacterMovement()->MaxWalkSpeed = (found->BaseRunSpeed / SpeedModifier);
	}

}

void ASnareTrap::EndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ABaseCharacter* found = Cast<ABaseCharacter>(OtherActor);
	if (found != nullptr)
	{
		found->GetCharacterMovement()->MaxWalkSpeed = found->BaseRunSpeed;
	}

}


