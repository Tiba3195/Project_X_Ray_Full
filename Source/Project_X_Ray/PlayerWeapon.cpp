//  _____           _           _    __   __  _____             |  __ \         (_)         | |   \ \ / / |  __ \            | |__) | __ ___  _  ___  ___| |_   \ V /  | |__) |__ _ _   _ |  ___/ _/ _ \| |/ _ \/ __| __|   > <   |  _  // _` | | | || |   | | | (_) | |  __/ (__| |_   / . \  | | \ \ (_| | |_| ||_|   |_|  \___/| |\___|\___|\__| /_/ \_\ |_|  \_\__,_|\__, |               _/ |                                     __/ |              |__/                                     |___/ 

#include "Project_X_Ray.h"
#include "PlayerWeapon.h"



APlayerWeapon::APlayerWeapon(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonGunMesh"));
	FP_Gun->SetupAttachment(RootComponent);
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FP_Gun->bCastDynamicShadow = false;
	//SEt Shadows
	FP_Gun->CastShadow = false;
	MuzzleOffset = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Offset"));
	MuzzleOffset->SetupAttachment(FP_Gun);
	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));

}

// Sets default values
APlayerWeapon::APlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonGunMesh"));
	FP_Gun->SetupAttachment(RootComponent);
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FP_Gun->bCastDynamicShadow = false;
	//SEt Shadows
	FP_Gun->CastShadow = false;
	MuzzleOffset = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle Offset"));
	MuzzleOffset->SetupAttachment(FP_Gun);
	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));

}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MuzzlePSC != NULL)
	{
		Age += DeltaTime;

		if (Age >= MaxMuzzleFlashAge)
		{
			MuzzlePSC->Deactivate();
			MuzzlePSC->DeactivateSystem();
		    MuzzlePSC = NULL;
			Age = 0;
		}
	}

}

void APlayerWeapon::Fire(AActor* sender, bool IsBot)
{
	if (MuzzleFlash)
	{
		if (MuzzlePSC != NULL)
		{
			MuzzlePSC->Deactivate();
			MuzzlePSC->DeactivateSystem();
			MuzzlePSC = NULL;
		}
		FRotator ShootDirection = MuzzleOffset->GetComponentRotation();
		MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MuzzleOffset);		
	}
	ProjectileFireControlComponent->Fire(MuzzleOffset, sender, IsBot);
}

