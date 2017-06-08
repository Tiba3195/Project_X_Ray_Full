// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyShip.h"

#include "EnemyBreacherShip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AEnemyBreacherShip : public AEnemyShip
{
	GENERATED_BODY()
	
public:
	AEnemyBreacherShip();
	AEnemyBreacherShip(const FObjectInitializer & PCIP);

	bool Deployed = false;
	UPROPERTY(EditAnywhere)
	UArrowComponent* SpawnOffset;


protected:
		virtual void Tick(float DeltaTime) override;
};
