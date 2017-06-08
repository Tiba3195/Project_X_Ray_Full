// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyShip.h"
#include "EnemyAssaultShip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AEnemyAssaultShip : public AEnemyShip
{
	GENERATED_BODY()

	
public:

	// Sets default values for this pawn's properties
	AEnemyAssaultShip();
	AEnemyAssaultShip(const FObjectInitializer & PCIP);

	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet1;

	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet2;

	UPROPERTY(EditAnywhere)
	UArrowComponent* NewMuzOffSet3;
	
};
