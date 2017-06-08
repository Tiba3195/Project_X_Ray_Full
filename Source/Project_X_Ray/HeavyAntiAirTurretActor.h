// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "HeavyAntiAirTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AHeavyAntiAirTurretActor : public ATurretActor
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	AHeavyAntiAirTurretActor();
	AHeavyAntiAirTurretActor(const FObjectInitializer & PCIP);

public:
	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet1;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet2;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet3;
	
};
