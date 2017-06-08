// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "DuelCannonTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ADuelCannonTurretActor : public ATurretActor
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	ADuelCannonTurretActor();
	ADuelCannonTurretActor(const FObjectInitializer & PCIP);



	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet1;


	

};
