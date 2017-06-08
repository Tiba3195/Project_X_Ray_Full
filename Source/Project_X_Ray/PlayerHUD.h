// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerHUDComponent.h"
#include "HUDWidgetComponent.h"
#include "PlayerHUD.generated.h"

UCLASS()
class PROJECT_X_RAY_API APlayerHUD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
public:
	// Sets default values for this pawn's properties
	APlayerHUD();
	APlayerHUD(const FObjectInitializer & PCIP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<UPlayerHUDComponent*> Slots;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UChildActorComponent* SelectionRoseComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TMap<FString, UHUDWidgetComponent*> ComponentLookUpTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveInfo)
		FString CurrentRoundStartText = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveInfo)
		FString NextWaveText = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveInfo)
		FString WaveOfWaveText = "";

	UFUNCTION(BlueprintCallable)
	float GetHealth(float BarSize);

	UFUNCTION(BlueprintCallable)
	float GetStamina(float BarSize);

	UFUNCTION(BlueprintNativeEvent)
	void WasClicked(UHUDWidgetComponent* target);
	virtual void WasClicked_Implementation(UHUDWidgetComponent* target);
};
