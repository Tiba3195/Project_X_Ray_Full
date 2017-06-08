// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "PlayerHUD.h"
#include "GlobalGameState.h"

static 	AGlobalGameState* ThisGS = nullptr;
APlayerHUD::APlayerHUD(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Arrow->SetupAttachment(RootComponent);
	Slots = TArray<UPlayerHUDComponent*>();
	SelectionRoseComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("Selection Rose Comp"));
	SelectionRoseComp->SetupAttachment(Arrow);
	ComponentLookUpTable=TMap<FString, UHUDWidgetComponent*>() ;
}
// Sets default values
APlayerHUD::APlayerHUD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Arrow->SetupAttachment(RootComponent);
	Slots = TArray<UPlayerHUDComponent*>();
	SelectionRoseComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("Selection Rose Comp"));
	SelectionRoseComp->SetupAttachment(Arrow);
	ComponentLookUpTable = TMap<FString, UHUDWidgetComponent*>();
}

// Called when the game starts or when spawned
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();

	//ThisGS = Cast<AGlobalGameState>(World->GetGameState());
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
	//	if (!ThisGS->IsValidLowLevel())
		//{
			ThisGS = Cast<AGlobalGameState>(World->GetGameState());
			//ThisGS->MainShip = this;
		//}
	}

	for (UActorComponent* hit : GetComponents())
	{
		UPlayerHUDComponent* tester = Cast<UPlayerHUDComponent>(hit);
		if (tester != nullptr)
		{
			Slots.Add(tester);
		}
	}

	for (UActorComponent* hit : GetComponents())
	{
		UHUDWidgetComponent* tester = Cast<UHUDWidgetComponent>(hit);
		if (tester != nullptr)
		{
			if (tester->LookUpName != "")
			{
				ComponentLookUpTable.Add(tester->LookUpName, tester);
			}		
		}
	}
	
}

// Called every frame
void APlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ThisGS == nullptr)
		return;

	CurrentRoundStartText = FString::FromInt(FMath::Max(ThisGS->CurrentRoundStartCountdownTime, 0));
	NextWaveText = FString::FromInt(FMath::Max(ThisGS->CurrentWTime, 0));
	WaveOfWaveText = FString::FromInt(FMath::Max(ThisGS->CurrentWave, 0)) + "/" + FString::FromInt(FMath::Max(ThisGS->Options.MaxWaves, 0));

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC != nullptr)
	{
		float LocationX;
		float LocationY;
		FVector camLoc;
		FRotator camRot;
		PC->GetMousePosition(LocationX, LocationY);
		FVector2D MousePosition(LocationX, LocationY);
		FVector2D ViewPos(0, 0);	

		for (UPlayerHUDComponent* hit : Slots)
		{
			if (hit->Type == HUDItemType::Button)
			{
				hit->SetSprite(hit->InactiveIcon);
			}			
		}

		if (ThisGS->MenuOpen)
		{
			// Do a trace and see if there the position intersects something in the world  
			for (UPlayerHUDComponent* hit : Slots)
			{
				if (hit->Type == HUDItemType::Button)
				{
					PC->ProjectWorldLocationToScreen(hit->GetComponentLocation(), ViewPos);
					float d = FVector::Distance(FVector(ViewPos.X, 0, ViewPos.Y), FVector(MousePosition.X, 0, MousePosition.Y));
					if (d <= 55)
					{
						hit->SetSprite(hit->ActiveIcon);

						if (PC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
						{
							if (hit->Command != "")
							{

								UHUDWidgetComponent* tester = ComponentLookUpTable[hit->Command];
							
								WasClicked(tester);
							}
						}
						break;
					}
				}
			}
		}

	}
}

void APlayerHUD::WasClicked_Implementation(UHUDWidgetComponent* target)
{

}

float APlayerHUD::GetHealth(float BarSize)
{

	if (!IsValid(ThisGS))
		return 0;
	if (ThisGS->Player == nullptr)
		return 0;
	if (!IsValid(ThisGS->Player))
		return 0;

	if (!ThisGS->Player->IsPendingKill())
	{
		float BarWidth = BarSize;
		float PercentToDraw = ThisGS->Player->Health / ThisGS->Player->MaxHealth;
		float HealthAmmount = BarWidth * PercentToDraw;
		return HealthAmmount;
	}
	else
	{
		return 0;
	}
}

float APlayerHUD::GetStamina(float BarSize)
{

	if (!ThisGS->IsValidLowLevel())
		return 0;

	if (ThisGS->Player == nullptr)
		return 0;

	if (!ThisGS->Player->IsPendingKill())
	{
		float BarWidth = BarSize;
		float PercentToDraw = ThisGS->Player->Stamina / ThisGS->Player->MaxStamina;
		float StaminaAmmount = BarWidth * PercentToDraw;
		return StaminaAmmount;
	}
	else
	{
		return 0;
	}
}

