// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SelectionRoseActor.h"
#include "SelectionRoseManager.generated.h"

UCLASS()
class PROJECT_X_RAY_API ASelectionRoseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectionRoseManager();
	ASelectionRoseManager(const class FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UArrowComponent* Forward;
};
