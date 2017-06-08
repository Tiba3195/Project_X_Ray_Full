// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "AntiAirTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AAntiAirTurretActor : public ATurretActor
{
	GENERATED_BODY()
	
	
public:

	AAntiAirTurretActor();
	AAntiAirTurretActor(const FObjectInitializer & PCIP);

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet1;
	
};
