// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemySpawnPoint.h"
#include "GlobalGameState.h"

UClass* ATPPCharacterClassHolder;
static AGlobalGameState*  BotSpawnerGS;
AEnemySpawnPoint::AEnemySpawnPoint(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ATPPCharacter> TheATPPCharacter(TEXT("/Game/BP_TPPCharacter.BP_TPPCharacter_C"));
	if (TheATPPCharacter.Class != NULL)
	{
		ATPPCharacterClassHolder = TheATPPCharacter.Class;
	}

}
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	//ThisGS = Cast<AGlobalGameState>(World->GetGameState());
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!BotSpawnerGS->IsValidLowLevel())
		//{
			BotSpawnerGS = Cast<AGlobalGameState>(World->GetGameState());
			//ThisGS->MainShip = this;
		//}
	}



	CurrentSpawnTime = BotSpawnerGS->CurrentBotSpawnIntervale;

	RegisterDelegate();
}

void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if ((CurrentSpawnTime >= BotSpawnerGS->CurrentBotSpawnIntervale )&& (BotSpawnerGS->HasRoundStarted == true))
	{
		CurrentSpawnTime = 0;
		HandleReSpawn();
	}	
	CurrentSpawnTime += DeltaTime;
}

void AEnemySpawnPoint::RegisterDelegate()
{


	

}
void AEnemySpawnPoint::HandleReSpawn()
{	

	ATPPCharacter* Player = GetWorld()->SpawnActor<ATPPCharacter>(ATPPCharacterClassHolder, GetActorLocation(), GetActorRotation());

	if (IsValid(Player))
	{
		Player->IsAlive = true;
		Player->GetController()->SetPawn(Player);
		Player->GetController()->Possess(Player);	
		BotSpawnerGS->NewActorSpawned(Player);
		BotSpawnerGS->IncrementBotCount();
		RegisterDelegate();
	}
}
void AEnemySpawnPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}