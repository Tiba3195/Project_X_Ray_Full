// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemyBreacherShip.h"
#include "EnemySpawnPoint.h"


UClass* SpawnpointClassHolder;
AEnemyBreacherShip::AEnemyBreacherShip(const FObjectInitializer & PCIP)
	: Super(PCIP)
{
	
	static ConstructorHelpers::FClassFinder<AEnemySpawnPoint> TheSpawner(TEXT("/Game/WorldObjects/BP_EnemySpawnPoint.BP_EnemySpawnPoint_C"));
	if (TheSpawner.Class != NULL)
	{
		SpawnpointClassHolder = TheSpawner.Class;
	}
	SpawnOffset = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Attachment"));
	SpawnOffset->SetupAttachment(SphereComponent);
	
}
// Sets default values
AEnemyBreacherShip::AEnemyBreacherShip()
	: Super()
{
	static ConstructorHelpers::FClassFinder<AEnemySpawnPoint> TheSpawner(TEXT("/Game/WorldObjects/BP_EnemySpawnPoint.BP_EnemySpawnPoint_C"));
	if (TheSpawner.Class != NULL)
	{
		SpawnpointClassHolder = TheSpawner.Class;
	}
	SpawnOffset = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Attachment"));
	SpawnOffset->SetupAttachment(SphereComponent);
}


void AEnemyBreacherShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AtTarget && !Deployed)
	{
		AEnemySpawnPoint* Spawner = GetWorld()->SpawnActor<AEnemySpawnPoint>(SpawnpointClassHolder, SpawnOffset->GetComponentLocation(), GetActorRotation());

		Deployed = true;// it gets messy without this, try it..... soe what happens

	}

}