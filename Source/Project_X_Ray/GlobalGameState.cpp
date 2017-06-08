// Fill out your copyright notice in the Description page of Project Settings.



#include "Project_X_Ray.h"

#include "GlobalGameState.h"


UClass* GridNodeActorClassHolder;
UClass* GridManagerActorClassHolder;

AGlobalGameState::AGlobalGameState(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AGridNodeActor> TheTurret(TEXT("/Game/WorldObjects/BP_GridNodeActor.BP_GridNodeActor_C"));
	if (TheTurret.Class != NULL)
	{
		GridNodeActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<AGridManagerActor> TheTurret2(TEXT("/Game/BP_GridManager.BP_GridManager_C"));
	if (TheTurret2.Class != NULL)
	{
		GridManagerActorClassHolder = TheTurret2.Class;
	}

	TurretHardPoints = TArray<ATurretHardPoint*>();
    ControlPointActors = TArray<AControlPointActor*>();
}

AGlobalGameState::AGlobalGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AGridNodeActor> TheTurret(TEXT("/Game/WorldObjects/BP_GridNodeActor.BP_GridNodeActor_C"));
	if (TheTurret.Class != NULL)
	{
		GridNodeActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<AGridManagerActor> TheTurret2(TEXT("/Game/BP_GridManager.BP_GridManager_C"));
	if (TheTurret2.Class != NULL)
	{
		GridManagerActorClassHolder = TheTurret2.Class;
	}

	TurretHardPoints = TArray<ATurretHardPoint*>();
	ControlPointActors = TArray<AControlPointActor*>();
}

void AGlobalGameState::BeginPlay()
{
	Super::BeginPlay();	

	CurrentBotCount = 0;
	BotsKilledByPlayer = 0;
	CurrentBotSpawnIntervale = Options.BotSpawnIntervale;
	CurrentWave = 0;
	HasRoundStarted = false;
	CurrentRoundStartCountdownTime = Options.RoundStartCountdownTime;
	CurrentWTime = Options.TimeBetweenWaves;

	//GetWorldTimerManager().SetTimer(RoundStartCountdownTimerHandle, this, &AGlobalGameState::RoundStartAdvanceTimer, 1.0f, true);


	if (GridNodeActorClassHolder != NULL && GridManagerActorClassHolder != NULL)
	{
		UWorld* World = GetWorld();
		if (World)
		{
		
			FActorSpawnParameters SpawnParams;
			GridManager = World->SpawnActor<AGridManagerActor>(GridManagerActorClassHolder, FVector(0, 0, 0) , FRotator(0.0f, 0.0f, 0.0f), SpawnParams);

			GridManager->Grid.Rows.SetNum(16);

			for (int x = 0; x < 16; x++)
			{
				for (int y = 0; y < 16; y++)
				{
					FVector2D pos = FVector2D(x * 256, y * 256);
		
					AGridNodeActor* NewGridCell = World->SpawnActor<AGridNodeActor>(GridNodeActorClassHolder, FVector(pos.X, pos.Y, 55) + FTransform(FRotator(0.0f, 0.0f, 0.0f)).TransformVector(FVector(-2048, -2048, 0)), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
					NewGridCell->Index = FVector2D(x, y);
					FGridNodeHolder NodeHolder = FGridNodeHolder();
					NodeHolder.GridNode = NewGridCell;
					GridManager->Grid.Rows[x].Cols.Add(NodeHolder);

				//	FGridNodeHolder XNodeHolder = GridManager->Grid.Rows[x].Cols[y];
				};
			};
		}
	}
}

void AGlobalGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player != nullptr)
	{
	AIngameHUD::SetPlayerHealth(Player->Health);
	AIngameHUD::SetPlayerMaxHealth(Player->MaxHealth);	


	for (ATurretHardPoint* hit : TurretHardPoints)
	{
		if (hit->HardpointBase != nullptr)
		{
			float d = FVector::Distance(Player->GetActorLocation(), hit->GetActorLocation());
			float HDiff = FMath::Abs((Player->GetActorLocation().Z - hit->GetActorLocation().Z));
		
			if ((d <= 1000) && (HDiff <= 100))
			{
				hit->HardpointBase->SetRenderCustomDepth(true);
				hit->HardpointBase->CustomDepthStencilValue = STENCIL_ITEMHIGHLIGHT; // or simply assign an int32 within 1-255 range

			}
			else
			{
				hit->HardpointBase->SetRenderCustomDepth(false);
				hit->HardpointBase->CustomDepthStencilValue = 0;
			}
		}
	}

	for (AControlPointActor* hit : ControlPointActors)
	{
		if (hit->CPMesh != nullptr)
		{
			float d = FVector::Distance(Player->GetActorLocation(), hit->GetActorLocation());
				if (d <= 1000)
				{
			
					hit->CPMesh->SetRenderCustomDepth(true);
					hit->CPMesh->CustomDepthStencilValue = STENCIL_ITEMHIGHLIGHT; // or simply assign an int32 within 1-255 range
				}
				else
				{
					hit->CPMesh->SetRenderCustomDepth(false);
					hit->CPMesh->CustomDepthStencilValue = 0;
				}

			}
		}

		}
}
void AGlobalGameState::NewActorSpawned(AActor * target)
{
	ActorSpwaned(target);
}
void AGlobalGameState::ActorSpwaned_Implementation(AActor* target)
{

}

void AGlobalGameState::StartGame()
{
	CurrentBotCount = 0;
	BotsKilledByPlayer = 0;
	CurrentBotSpawnIntervale = Options.BotSpawnIntervale;
	CurrentWave = 0;
	HasRoundStarted = false;
	CurrentRoundStartCountdownTime = Options.RoundStartCountdownTime;
	CurrentWTime = Options.TimeBetweenWaves;
	GetWorldTimerManager().SetTimer(RoundStartCountdownTimerHandle, this, &AGlobalGameState::RoundStartAdvanceTimer, 1.0f, true);
	
}
void AGlobalGameState::ToggleViewMode()
{
	AIngameHUD::ToggleViewMode();
}

void AGlobalGameState::RoundStartAdvanceTimer()
{
	--CurrentRoundStartCountdownTime;
	//UpdateTimerDisplay();
	if (CurrentRoundStartCountdownTime < 1)
	{	
		//We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(RoundStartCountdownTimerHandle);
		RoundStartCountdownHasFinished();
	}
}

void AGlobalGameState::RoundStartCountdownHasFinished()
{
	HasRoundStarted = true;
	CurrentWave += 1;
	GetWorldTimerManager().SetTimer(WaveInterCountdownTimerHandle, this, &AGlobalGameState::WaveInterAdvanceTimer, 1.0f, true);
}

void AGlobalGameState::WaveInterAdvanceTimer()
{

	--CurrentWTime;
	//UpdateTimerDisplay();
	if (CurrentWTime < 1)
	{		
		//We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(WaveInterCountdownTimerHandle);
		WaveInterCountdownHasFinished();
	}

}

void AGlobalGameState::WaveInterCountdownHasFinished()
{
	CurrentWave = FMath::Min(CurrentWave, Options.MaxWaves);
	if (CurrentWave < Options.MaxWaves)
	{
		CurrentRoundStartCountdownTime = Options.RoundStartCountdownTime;
		CurrentWTime = Options.TimeBetweenWaves;
		CurrentBotSpawnIntervale = CurrentBotSpawnIntervale * Options.BotSpawnIntervaleMutator;
		HasRoundStarted = false;
		GetWorldTimerManager().SetTimer(RoundStartCountdownTimerHandle, this, &AGlobalGameState::RoundStartAdvanceTimer, 1.0f, true);
	}
	else
	{
		HasRoundStarted = false;
	}

	//GetWorldTimerManager().SetTimer(WaveInterCountdownTimerHandle, this, &AGlobalGameState::WaveInterAdvanceTimer, 1.0f, true);
}

void AGlobalGameState::IncrementBotCount()
{
	CurrentBotCount += 1;
}

void AGlobalGameState::DecrementBotCount(bool killedbyplayer)
{
	if (killedbyplayer)
	{
		BotsKilledByPlayer += 1;
	}
	CurrentBotCount -= 1;
}



INT32 AGlobalGameState::GetCurrentHardPointIndex()
{
	return INT32();
}

void AGlobalGameState::SetCurrentHardPointIndex(INT32 index)
{
	MainShip->CurrentHardPointIndex = index;
}

void AGlobalGameState::DisableInputEX()
{
	AIngameHUD::DisableInputEX();
}

void AGlobalGameState::EnableInputEX()
{
	AIngameHUD::EnableInputEX();
}

void AGlobalGameState::UsableInView()
{
	AIngameHUD::UsableInView();
}

void AGlobalGameState::NoUsableInView()
{
	AIngameHUD::NoUsableInView();
}

void AGlobalGameState::HardPointInView()
{
	AIngameHUD::HardPointInView();
}

void AGlobalGameState::NoHardPointInView()
{
	AIngameHUD::NoHardPointInView();
}

void AGlobalGameState::showMenu()
{
	if (MenuOpen)
	{
		MenuOpen = false;
	}
	else
	{
		MenuOpen = true;
	}

	AIngameHUD::showMenu();
}

void AGlobalGameState::ClearSelected()
{
	AIngameHUD::ClearSelected();
}

void AGlobalGameState::SetTurret(ATurretActor * turret)
{
	AIngameHUD::SetTurret(turret);
}

void AGlobalGameState::SetHardPoint(ATurretHardPoint * hardpoint)
{
	AIngameHUD::SetHardPoint(hardpoint);
}

void AGlobalGameState::AddControlPoint(AControlPointActor * controlPoint)
{
	ControlPointActors.Add(controlPoint);
}

AControlPointActor * AGlobalGameState::GetControlPoint()
{
	int index = rand() % ControlPointActors.Num();
	return ControlPointActors[index];
}

AControlPointActor * AGlobalGameState::GetControlPoint(FVector thislocation)
{


	return nullptr;
}


void AGlobalGameState::AddTurretToHardPoint(FString TurretName,INT32 index)
{
	int counter = TurretHardPoints.Num();
	if (index >= 0 && index <= counter)
	{
	  TurretHardPoints[index]->BuildTurret(TurretName);
	}
}