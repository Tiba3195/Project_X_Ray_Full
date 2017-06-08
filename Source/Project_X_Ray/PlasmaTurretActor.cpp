// Fill out your copyright notice in the Description page of Project Settings.
// Liams code
#include "Project_X_Ray.h"
#include "PlasmaTurretActor.h"


APlasmaTurretActor::APlasmaTurretActor(const class FObjectInitializer& PCIP)	
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	//Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	Swivel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwivelMesh"));
	BarrelForward = CreateDefaultSubobject<UArrowComponent>(TEXT("BarrelForward"));
	//This was a super sucky bug, took me hrs to find out the correct way to do this!!
	//TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);

	Base->SetupAttachment(TurretAttachment);
	
//	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(Base);
	Swivel->SetupAttachment(Forward);
	BarrelForward->SetupAttachment(Swivel);
	Gun->SetupAttachment(BarrelForward);





	NewMuzOffSet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

	NewMuzOffSet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 2"));

	AddMuzzleOffSet(NewMuzOffSet2);

	NewMuzOffSet3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Off Set 3"));

	AddMuzzleOffSet(NewMuzOffSet3);

//	ThisPwan = CreateDefaultSubobject<ATurretPawn>(TEXT("Turret Pawn"));


//	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
//	MuzzleOffsets = TArray<UArrowComponent*>();
//	DamageEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Damage Effect"));
	//DamageEffect->SetupAttachment(Base);
//	DethEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Deth Effect"));
	//DethEffect->SetupAttachment(Base);
//	MaxHealth = Health;

}



// Sets default values
APlasmaTurretActor::APlasmaTurretActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	//Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	Swivel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwivelMesh"));
	BarrelForward = CreateDefaultSubobject<UArrowComponent>(TEXT("BarrelForward"));
	//This was a super sucky bug, took me hrs to find out the correct way to do this!!
	//TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);

	Base->SetupAttachment(TurretAttachment);

	//	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(Base);
	Swivel->SetupAttachment(Forward);
	BarrelForward->SetupAttachment(Swivel);
	Gun->SetupAttachment(BarrelForward);


//	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	//MuzzleOffsets = TArray<UArrowComponent*>();
	//DamageEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Damage Effect"));
	//DamageEffect->SetupAttachment(Base);
	//DethEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Deth Effect"));
	//DethEffect->SetupAttachment(Base);
//	MaxHealth = Health;

}


void APlasmaTurretActor::TurnToFace(AActor * other, float DeltaTime)
{
	FVector Direction = other->GetActorLocation() - Forward->GetComponentLocation();
	FRotator NewControlRotation = Direction.Rotation();

	NewControlRotation.Pitch = 0;
	NewControlRotation.Roll = 0;

	float diff = FRotator::NormalizeAxis(NewControlRotation.Yaw - Forward->GetComponentRotation().Yaw);
	if ((diff <= 15.0f) && (diff >= -15.0f))
	{
		CanFire = true;
	}
	else
	{
		CanFire = false;
	}

	NewControlRotation.Normalize();
	NewControlRotation.Normalize();

	Forward->SetWorldRotation(FMath::RInterpConstantTo(Forward->GetComponentRotation(), NewControlRotation, DeltaTime, TurnSpeed));

	Direction = other->GetActorLocation() - BarrelForward->GetComponentLocation();
	FRotator BarrelPitchRotator = Direction.Rotation();
	FRotator NewR = Forward->GetComponentRotation();
	float pitch = BarrelForward->GetComponentRotation().Pitch;
	NewR.Pitch = pitch;

	BarrelForward->SetWorldRotation(FMath::RInterpConstantTo(NewR, BarrelPitchRotator, DeltaTime, TurnSpeed ));
}
