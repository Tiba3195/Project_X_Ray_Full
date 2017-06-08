// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "TPPCharacter.h"
#include "TopdownCppPlayerController.h"
#include "FlyingAIController.h"
#include "EnemySpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AEnemySpawnPoint : public APlayerStart
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AEnemySpawnPoint();
	AEnemySpawnPoint(const FObjectInitializer & PCIP);
	void RegisterDelegate();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);
	UPROPERTY(EditAnywhere)
	bool ShipSpawner  = false;
	UPROPERTY(EditAnywhere)
	float SpawnTime = 25.0f;
	float CurrentSpawnTime = 25.0f;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleReSpawn();

};
