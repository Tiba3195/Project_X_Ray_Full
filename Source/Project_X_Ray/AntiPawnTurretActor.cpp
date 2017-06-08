// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "AntiPawnTurretActor.h"




AAntiPawnTurretActor::AAntiPawnTurretActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;

	NewMuzOffSet = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	NewMuzOffSet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

	NewMuzOffSet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 2"));

	AddMuzzleOffSet(NewMuzOffSet2);

	NewMuzOffSet3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 3"));

	AddMuzzleOffSet(NewMuzOffSet3);


}


AAntiPawnTurretActor::AAntiPawnTurretActor()
	: Super()
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NewMuzOffSet = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	NewMuzOffSet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

	NewMuzOffSet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 2"));

	AddMuzzleOffSet(NewMuzOffSet2);

	NewMuzOffSet3= CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 3"));

	AddMuzzleOffSet(NewMuzOffSet3);

}