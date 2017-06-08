// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemyAssaultShip.h"




AEnemyAssaultShip::AEnemyAssaultShip(const FObjectInitializer & PCIP)
	: Super(PCIP)
{
	

	NewMuzOffSet = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	NewMuzOffSet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

	NewMuzOffSet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 2"));

	AddMuzzleOffSet(NewMuzOffSet2);

	NewMuzOffSet3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 3"));

	AddMuzzleOffSet(NewMuzOffSet3);

	//	SphereComponent->SetupAttachment(Forward);
}
// Sets default values
AEnemyAssaultShip::AEnemyAssaultShip()
{
	
	NewMuzOffSet = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	NewMuzOffSet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

	NewMuzOffSet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 2"));

	AddMuzzleOffSet(NewMuzOffSet2);

	NewMuzOffSet3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 3"));

	AddMuzzleOffSet(NewMuzOffSet3);
}