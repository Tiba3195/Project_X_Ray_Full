
#pragma once

#include "Components/WidgetComponent.h"
#include "HUDWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_X_RAY_API UHUDWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public :


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FString LookUpName = "";
	
	void SetVisable(bool viable);
	
	
};
