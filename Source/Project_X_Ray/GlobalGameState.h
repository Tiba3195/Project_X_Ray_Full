// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MainCharacter.h"
#include "MotherShip.h"
#include "TurretHardPoint.h"
#include "GridManagerActor.h"
#include "GridNodeActor.h"
#include "TurretActor.h"
#include "IngameHUD.h"
#include "ControlPointActor.h"
#include "GameFramework/GameStateBase.h"
#include "GlobalGameState.generated.h"



USTRUCT(BlueprintType)
struct FGameOptions: public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
		int32 MaxWaves = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
		int32 RoundStartCountdownTime = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
		int32 TimeBetweenWaves = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
		float BotSpawnIntervale = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
		float BotSpawnIntervaleMutator = 0.5f;
	//~

	//default properties

	FGameOptions()
	{
		
			 MaxWaves = 3;		
			 RoundStartCountdownTime = 30;		
			 TimeBetweenWaves = 60;		
			 BotSpawnIntervale = 15.0f;	
			 BotSpawnIntervaleMutator = 0.5f;
	}

};


/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AGlobalGameState : public AGameStateBase
{
	GENERATED_BODY()

	AGlobalGameState(const class FObjectInitializer& PCIP);
	AGlobalGameState();



protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	static void ToggleViewMode();

	INT32 GetCurrentHardPointIndex();
	void SetCurrentHardPointIndex(INT32 index);

	 void DisableInputEX();
	 void EnableInputEX();
	 void UsableInView();
	 void NoUsableInView();
	 void HardPointInView();
	 void NoHardPointInView();
	 void showMenu();
	 void ClearSelected();

	 void SetTurret(ATurretActor* turret);

	 void SetHardPoint(ATurretHardPoint* hardpoint);

	 void AddControlPoint(AControlPointActor* controlPoint);

	 UFUNCTION(BlueprintCallable)
	 AControlPointActor* GetControlPoint();
	 //UFUNCTION(BlueprintCallable)
	 AControlPointActor* GetControlPoint(FVector thislocation);

	 inline static bool ConstPredicateHealth(const ABaseCharacter& ip1, const ABaseCharacter& ip2)
	 {
		 return (ip1.Health < ip2.Health);
	 }

	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	AMotherShip* MainShip = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	float TimeBeforeRoundStart= 30.0f;

	float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	AMainCharacter* Player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<ATurretHardPoint*> TurretHardPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<AControlPointActor*> ControlPointActors;

	

	void AddTurretToHardPoint(FString TurretName, INT32 index);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
		AGridManagerActor* GridManager = nullptr;


	void RoundStartAdvanceTimer();

	void RoundStartCountdownHasFinished();

	FTimerHandle RoundStartCountdownTimerHandle;

	void WaveInterAdvanceTimer();

	void WaveInterCountdownHasFinished();

	void IncrementBotCount();

	void DecrementBotCount(bool killedbyplayer);

	FTimerHandle WaveInterCountdownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)
	FGameOptions Options = FGameOptions();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer)
	bool HasRoundStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	float EnemyDetectionRange = 2000;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer)
	int32 CurrentRoundStartCountdownTime = 0;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer)
    int32 CurrentWTime = 0;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer)
	int32 CurrentWave = 0;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
	float CurrentBotSpawnIntervale = 15.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
		int32 CurrentBotCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
		int32 BotsKilledByPlayer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		bool MenuOpen = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlay)
		bool HasGameStarted = false;
	void NewActorSpawned(AActor* target);

	UFUNCTION(BlueprintNativeEvent)
		void ActorSpwaned(AActor* target);
	virtual void ActorSpwaned_Implementation(AActor* target);

	UFUNCTION(BlueprintCallable)
		void StartGame();
//	virtual void StartGame_Implementation();


};
