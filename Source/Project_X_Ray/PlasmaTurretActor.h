// Fill out your copyright notice in the Description page of Project Settings.
// Liams code
#pragma once

#include "TurretActor.h"
#include "PlasmaTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API APlasmaTurretActor : public ATurretActor
{
	GENERATED_BODY()
public:
	APlasmaTurretActor();
	APlasmaTurretActor(const FObjectInitializer & PCIP);
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Swivel;

	void TurnToFace(AActor* other, float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UArrowComponent* BarrelForward;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet1;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet2;

	UPROPERTY(EditAnywhere)
		UArrowComponent* NewMuzOffSet3;

};
