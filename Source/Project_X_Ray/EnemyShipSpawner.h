// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "EnemyShipSpawner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AEnemyShipSpawner : public APlayerStart
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyShipSpawner();
	AEnemyShipSpawner(const FObjectInitializer & PCIP);
	void RegisterDelegate();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);	
	UPROPERTY(EditAnywhere)
	float SpawnTime = 25.0f;
	float CurrentSpawnTime = 25.0f;
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> TargetPoint;

	UPROPERTY(EditAnywhere)
		bool AssaultShipSpawner = true;

	UPROPERTY(EditAnywhere)
		bool SingleSpawnOnly;

	bool Spawned;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleReSpawn();

	
};
