// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretHardPoint.h"
#include "GlobalGameState.h"
#include "MediumTurretActor.h"
#include "LightTurretActor.h"
#include "HeavyTurretActor.h"

#include "HeavyAntiAirTurretActor.h"
#include "AntiAirTurretActor.h"
#include "DuelCannonTurretActor.h"
#include "AntiPawnTurretActor.h"
#include "PlasmaTurretActor.h"


//the turret classes that will be imported and filled with a blueprint
UClass* HeavyTurretActorClassHolder;
UClass* MediumTurretActorClassHolder;
UClass* LightTurretActorClassHolder;

UClass* HeavyAntiAirTurretActorClassHolder;
UClass* AntiAirTurretActorClassHolder;
UClass* DuelTurretActorClassHolder;
UClass* AntiPawnTurretActorClassHolder;

UClass* TurretActorClassHolder;

UClass* PlasmaTurretClassHolder;

//Names of the blueprints for checking if we can build a turret type
static FString HeavyTurretName = "/Game/Turrets/BP_HeavyTurretActor.BP_HeavyTurretActor_C";
static FString MediumTurretTurretName = "/Game/Turrets/BP_MediumTurretActor.BP_MediumTurretActor_C";
static FString LightTurretName = "/Game/Turrets/BP_LightTurretActor.BP_LightTurretActor_C";

static FString HeavyAntiAirTurretName = "/Game/Turrets/BP_HeavyAntiAirTurretActor.BP_HeavyAntiAirTurretActor_C";
static FString AntiAirTurretTurretName = "/Game/Turrets/BP_AntiAirTurretActor.BP_AntiAirTurretActor_C";
static FString DuelTurretName = "/Game/Turrets/BP_DuelCannonTurretActor.BP_DuelCannonTurretActor_C";

static FString AntiPawnTurretName = "/Game/Turrets/BP_AntiPawnTurretActor.BP_AntiPawnTurretActor_C";

static FString PlasmaTurretName = "/Game/Turrets/BP_PlasmaTurretActor.BP_PlasmaTurretActor_C";

ATurretHardPoint::ATurretHardPoint(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HardpointBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HardpointBase Mesh"));
    HardpointBase->SetupAttachment(RootComponent);

	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(HardpointBase);

	HardPointAttachment = CreateDefaultSubobject<UHardPointAttachment>(TEXT("HardPoint Attachment"));
	HardPointAttachment->SetupAttachment(HardpointBase);
	//TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 113.179932));


	UWorld* World = GetWorld();
	if (World)
	{
		
	}
	//importing blueprints

	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret(TEXT("/Game/Turrets/BP_LightTurretActor.BP_LightTurretActor_C"));
	if (TheTurret.Class != NULL)
	{
		LightTurretActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret2(TEXT("/Game/Turrets/BP_MediumTurretActor.BP_MediumTurretActor_C"));
	if (TheTurret2.Class != NULL)
	{
		MediumTurretActorClassHolder = TheTurret2.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret3(TEXT("/Game/Turrets/BP_HeavyTurretActor.BP_HeavyTurretActor_C"));
	if (TheTurret3.Class != NULL)
	{
		HeavyTurretActorClassHolder = TheTurret3.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret4(TEXT("/Game/Turrets/BP_TurretActor.BP_TurretActor_C"));
	if (TheTurret4.Class != NULL)
	{
		TurretActorClassHolder = TheTurret4.Class;
	}


	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret5(TEXT("/Game/Turrets/BP_HeavyAntiAirTurretActor.BP_HeavyAntiAirTurretActor_C"));
	if (TheTurret5.Class != NULL)
	{
		HeavyAntiAirTurretActorClassHolder = TheTurret5.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret6(TEXT("/Game/Turrets/BP_AntiAirTurretActor.BP_AntiAirTurretActor_C"));
	if (TheTurret6.Class != NULL)
	{
		AntiAirTurretActorClassHolder = TheTurret6.Class;
	}

	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret8(TEXT("/Game/Turrets/BP_DuelCannonTurretActor.BP_DuelCannonTurretActor_C"));
	if (TheTurret8.Class != NULL)
	{
		DuelTurretActorClassHolder = TheTurret8.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret9(TEXT("/Game/Turrets/BP_AntiPawnTurretActor.BP_AntiPawnTurretActor_C"));
	if (TheTurret9.Class != NULL)
	{
		AntiPawnTurretActorClassHolder = TheTurret9.Class;
	}

	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret10(TEXT("/Game/Turrets/BP_PlasmaTurretActor.BP_PlasmaTurretActor_C"));
	if (TheTurret10.Class != NULL)
	{
		PlasmaTurretClassHolder = TheTurret10.Class;
	}

}


ATurretHardPoint::ATurretHardPoint()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	HardpointBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HardpointBase Mesh"));
	HardpointBase->SetupAttachment(RootComponent);


	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(HardpointBase);
	//TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f,113.179932));
	HardPointAttachment = CreateDefaultSubobject<UHardPointAttachment>(TEXT("HardPoint Attachment"));
	HardPointAttachment->SetupAttachment(HardpointBase);


}


void ATurretHardPoint::RegisterDelegate()
{
}

void ATurretHardPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
		Super::EndPlay(EndPlayReason);

}

void ATurretHardPoint::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();

	UWorld* World = GetWorld();
	AGlobalGameState* GS= Cast<AGlobalGameState>(World->GetGameState());
	if (GS)
	{
		//adding the hardpoint to the gamestate and saving the index for fast lookups
		int counter = GS->TurretHardPoints.Num();
		HardPointIndex = counter;

		GS->TurretHardPoints.Add(this);
	}


//	BuildTurret();
}

void ATurretHardPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//builds the base turret actor blueprint
void ATurretHardPoint::BuildTurret()
{
	if (TurretActorClassHolder != NULL)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			//SpawnParams.Instigator = this;
			ATurretActor* temp = Cast<ATurretActor>(TurretActorClassHolder->GetDefaultObject());
			FVector tempV = temp->TurretAttachment->RelativeLocation;
			FVector tempV2 = TurretAttachment->RelativeLocation;
			FVector tempV3 = GetActorLocation() + tempV2 + tempV;
			
			ATurretActor* NewTurret = World->SpawnActor<ATurretActor>(TurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	

		}
	}
}
//builds a turret based on the name of the blueprint passed in, the name will come from the selection rose menu actor
void ATurretHardPoint::BuildTurret(FString TurretName)
{
	UWorld* World = GetWorld();
	if (World)
	{
	
		AGlobalGameState* GS= Cast<AGlobalGameState>(World->GetGameState());

		FActorSpawnParameters SpawnParams;

		if (TurretName == HeavyTurretName)
		{
			if (HeavyTurretActorClassHolder != NULL)
			{		
			
				//getting a temp copy of this turret so we can find all the offsets, proly a much better way to do this. With an array like the muzzle offsets
				AHeavyTurretActor* temp = Cast<AHeavyTurretActor>(HeavyTurretActorClassHolder->GetDefaultObject());
				//finding the attachment offset for world placement
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				//spawning the turret we will se in the game
				AHeavyTurretActor* NewTurret = World->SpawnActor<AHeavyTurretActor>(HeavyTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				//telling the gamestae we just built a turret
				GS->NewActorSpawned(NewTurret);
			    //cleaning up
				temp->Destroy();
			}
		}
		if (TurretName == MediumTurretTurretName)
		{
			if (MediumTurretActorClassHolder != NULL)
			{
				AMediumTurretActor* temp = Cast<AMediumTurretActor>(MediumTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AMediumTurretActor* NewTurret = World->SpawnActor<AMediumTurretActor>(MediumTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}
		if (TurretName == LightTurretName)
		{
			if (LightTurretActorClassHolder != NULL)
			{
				ALightTurretActor* temp = Cast<ALightTurretActor>(LightTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				ALightTurretActor* NewTurret = World->SpawnActor<ALightTurretActor>(LightTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
			}
		}
		

		if (TurretName == HeavyAntiAirTurretName)
		{
			if (HeavyAntiAirTurretActorClassHolder != NULL)
			{

				AHeavyAntiAirTurretActor* temp = Cast<AHeavyAntiAirTurretActor>(HeavyAntiAirTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AHeavyAntiAirTurretActor* NewTurret = World->SpawnActor<AHeavyAntiAirTurretActor>(HeavyAntiAirTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}
		if (TurretName == AntiAirTurretTurretName)
		{
			if (AntiAirTurretActorClassHolder != NULL)
			{
				AAntiAirTurretActor* temp = Cast<AAntiAirTurretActor>(AntiAirTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AAntiAirTurretActor* NewTurret = World->SpawnActor<AAntiAirTurretActor>(AntiAirTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}
		if (TurretName == DuelTurretName)
		{
			if (DuelTurretActorClassHolder != NULL)
			{
				ADuelCannonTurretActor* temp = Cast<ADuelCannonTurretActor>(DuelTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				ADuelCannonTurretActor* NewTurret = World->SpawnActor<ADuelCannonTurretActor>(DuelTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}

		if (TurretName == AntiPawnTurretName)
		{
			if (AntiPawnTurretActorClassHolder != NULL)
			{
				AAntiPawnTurretActor* temp = Cast<AAntiPawnTurretActor>(AntiPawnTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AAntiPawnTurretActor* NewTurret = World->SpawnActor<AAntiPawnTurretActor>(AntiPawnTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}

		if (TurretName == PlasmaTurretName)
		{
			if (PlasmaTurretClassHolder != NULL)
			{
				APlasmaTurretActor* temp = Cast<APlasmaTurretActor>(PlasmaTurretClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				APlasmaTurretActor* NewTurret = World->SpawnActor<APlasmaTurretActor>(PlasmaTurretClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				GS->NewActorSpawned(NewTurret);
				temp->Destroy();
			}
		}

	}
}

void ATurretHardPoint::RunCommand(FString command)
{

	BuildTurret(command);

}
