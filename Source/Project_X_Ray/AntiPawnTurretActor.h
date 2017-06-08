// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "AntiPawnTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AAntiPawnTurretActor : public ATurretActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAntiPawnTurretActor();
	AAntiPawnTurretActor(const FObjectInitializer & PCIP);
	
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
