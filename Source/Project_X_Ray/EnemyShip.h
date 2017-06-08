// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "ProjectileFireControlComponent.h"
#include "DonAINavigation/Classes/DonNavigatorInterface.h"
#include "EnemyShip.generated.h"

UCLASS()
class PROJECT_X_RAY_API AEnemyShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyShip();
	AEnemyShip(const FObjectInitializer & PCIP);



	UPROPERTY(EditAnywhere)
		FVector flightDestination = FVector(0.0f,0.0f,0.0f);

	int currenttargetindex=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float AttackRange = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UProjectileFireControlComponent* ProjectileFireControlComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float FireRate = 0.6f;

	UPROPERTY(EditAnywhere)
		TArray<UArrowComponent*> MuzzleOffsets;
	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Health = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MinHealth = 1500;

	bool AtTarget = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TurnToFace(AActor* other);
	float CurrentFireRate=0;
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** Pawn suicide */
	virtual void Suicide();

	/** play effects on hit */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void AddMuzzleOffSet(UArrowComponent* MuzzleOffset);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input'
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Gun;

	UPROPERTY(EditAnywhere)
		UArrowComponent* Forward;
	UPROPERTY(EditAnywhere)
		UArrowComponent* ShipForward;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, Category = Mesh)
		USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> TargetPoint;

	void AddMovement(FVector WorldDirection, float ScaleValue, bool bForce /*=false*/);

	void TurnToFace(FVector Direction);


	static FORCEINLINE bool VTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		TArray<FOverlapResult>& HitOut,
		ECollisionChannel TraceChannel = ECC_Pawn
	) {
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		//TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);
		//TraceParams.AddIgnoredComponent(UStaticMeshComponent::GetArchetype)
		//Re-initialize hit info
		HitOut = TArray<FOverlapResult>();

		//Get World Source
		TObjectIterator< APlayerController > ThePC;
		if (!ThePC) return false;


		return ThePC->GetWorld()->OverlapMultiByProfile(
			HitOut,
			Start,
			FQuat(),
			"pawn",
			FCollisionShape::MakeSphere(Radius),
			TraceParams
		);
	}
//	inline static bool ConstPredicate(const ATurretActor& ip1, const ATurretActor& ip2)
	//{
	//	return (ip1.Health < ip2.Health);
	//}

};
