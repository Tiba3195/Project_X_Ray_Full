// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "MediumTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AMediumTurretActor : public ATurretActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMediumTurretActor();
	AMediumTurretActor(const FObjectInitializer & PCIP);

	
	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet1;
	
};
