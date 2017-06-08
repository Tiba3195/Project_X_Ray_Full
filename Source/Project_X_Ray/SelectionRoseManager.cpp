// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "SelectionRoseManager.h"


// Sets default values
ASelectionRoseManager::ASelectionRoseManager(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Forward->SetupAttachment(RootComponent);
	

}
// Sets default values
ASelectionRoseManager::ASelectionRoseManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Forward->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASelectionRoseManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectionRoseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

