// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UsableActor.h"
#include "BaseTrapActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ABaseTrapActor : public AUsableActor
{
	GENERATED_BODY()
	
public:
	ABaseTrapActor();
	ABaseTrapActor(const FObjectInitializer & PCIP);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SquishedCube;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UParticleSystem* TrapEffect;
	float CurrentFrameDelta = 0;

	bool IsEffect = false;

	UFUNCTION()
	virtual	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
		float EffectHeightOffset = 5.0f;

	UPROPERTY(EditAnywhere)
		float SpeedModifier = 8.0f;


};
