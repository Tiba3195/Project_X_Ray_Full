//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#pragma once

#include "BaseTrapActor.h"
#include "SnareTrap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ASnareTrap : public ABaseTrapActor
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION()
		virtual	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


	
};
