// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemyShipSpawner.h"
#include "EnemyShip.h"
#include "EnemyAssaultShip.h"
#include "EnemyBreacherShip.h"


UClass* AssaultShipClassHolder;
UClass* BreachingShipClassHolder;
AEnemyShipSpawner::AEnemyShipSpawner(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AEnemyAssaultShip> TheATPPCharacter(TEXT("/Game/WorldObjects/BP_EnemyAssaultShip.BP_EnemyAssaultShip_C"));
	if (TheATPPCharacter.Class != NULL)
	{
		AssaultShipClassHolder = TheATPPCharacter.Class;
	}
	static ConstructorHelpers::FClassFinder<AEnemyBreacherShip> TheATPPCharacter2(TEXT("/Game/WorldObjects/BP_EnemyBreacherShip.BP_EnemyBreacherShip_C"));
	if (TheATPPCharacter2.Class != NULL)
	{
		BreachingShipClassHolder = TheATPPCharacter2.Class;
	}
}
AEnemyShipSpawner::AEnemyShipSpawner()
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyShipSpawner::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpawnTime = SpawnTime;

	RegisterDelegate();
}

void AEnemyShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSpawnTime >= SpawnTime)
	{
		CurrentSpawnTime = 0;
		HandleReSpawn();
	}
	CurrentSpawnTime += DeltaTime;
}

void AEnemyShipSpawner::RegisterDelegate()
{
}
void AEnemyShipSpawner::HandleReSpawn()
{


	if (SingleSpawnOnly && Spawned)
	{
		return;
	}


	if (AssaultShipSpawner)
	{
		AEnemyAssaultShip* Ship = GetWorld()->SpawnActor<AEnemyAssaultShip>(AssaultShipClassHolder, GetActorLocation(), GetActorRotation());

		if (IsValid(Ship))
		{
			Ship->GetController()->SetPawn(Ship);
			Ship->GetController()->Possess(Ship);
			//if (TargetPoint != nullptr)
			//	{
			Ship->TargetPoint = TargetPoint;
			//	}
			Spawned = true;
			RegisterDelegate();
		}
	}
	else
	{
		AEnemyBreacherShip* Ship = GetWorld()->SpawnActor<AEnemyBreacherShip>(BreachingShipClassHolder, GetActorLocation(), GetActorRotation());

		if (IsValid(Ship))
		{
			Ship->GetController()->SetPawn(Ship);
			Ship->GetController()->Possess(Ship);
			//if (TargetPoint != nullptr)
			//	{
			Ship->TargetPoint = TargetPoint;
			//	}
			Spawned = true;
			RegisterDelegate();
		}
	}

}
void AEnemyShipSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}