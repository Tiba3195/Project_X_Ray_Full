// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TurretAttachmenttComponent.h"
#include "UsableActor.h"
#include "ProjectileFireControlComponent.h"
#include "BaseCharacter.h"
#include "MainCharacter.h"
#include "TPPCharacter.h"
#include "EnemyShip.h"
#include "TurretPawn.h"
#include "TurretActor.generated.h"





/**
 * 
 */



UCLASS()
class PROJECT_X_RAY_API ATurretActor : public AUsableActor
{
	GENERATED_BODY()
	
	

public:
	// Sets default values for this actor's properties
	ATurretActor();
	ATurretActor(const FObjectInitializer & PCIP);

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		float FireRate = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		bool CanFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		float TurnSpeed =75.0f;

	float CurrentFireRate=0.0f;
	float CurrentTurretActiveCounter = 3.0f;
	ATPPCharacter* found;
	AEnemyShip* AntiAirfound;

	void RegisterDelegate();

	UPROPERTY(EditAnywhere)
		FireMode TurretFireMode = FireMode::AlphaBurst;

	UPROPERTY(EditAnywhere)
		TArray<UArrowComponent*> MuzzleOffsets;
	void AddMuzzleOffSet(UArrowComponent* MuzzleOffset);
//	void OnBeginTriggerOverlap( AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnBeginTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void EndPlay(const EEndPlayReason::Type EndPlayReason);



	//Sets the Camera Offset
	UPROPERTY(EditAnywhere)
		FVector FirstPersonCameraOffset = FVector(0.0f, 0.0f, 50.0f);

	//Sets the Camera Offset
	UPROPERTY(EditAnywhere)
		FVector ThirdPersonCameraOffset = FVector(0.0f, 0.0f, 0.0f);

	//Sets the Camera Rotation
	UPROPERTY(EditAnywhere)
		FRotator ThirdPersonCameraRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Gun;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Base;

//	UPROPERTY(EditAnywhere)
	//	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTurretAttachmenttComponent* TurretAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UProjectileFireControlComponent* ProjectileFireControlComponent;

	virtual void TurnToFace(AActor* other, float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float AttackRange = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UArrowComponent* Forward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool IsAntiAir = false;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Health = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MinHealth = 1500;

	UPROPERTY(EditAnywhere)
		UParticleSystem* DamageEffect;
	UPROPERTY(EditAnywhere)
		UParticleSystem* DethEffect;



	/**
	* Kills pawn.  Server/authority only.
	* @param KillingDamage - Damage amount of the killing blow
	* @param DamageEvent - Damage event of the killing blow
	* @param Killer - Who killed this pawn
	* @param DamageCauser - the Actor that directly caused the damage (i.e. the Projectile that exploded, the Weapon that fired, etc)
	* @returns true if allowed
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** Pawn suicide */
	virtual void Suicide();

	/** play effects on hit */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

		float MaxHealth = 0;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	 void GroundTurretTick(float DeltaTime);
	 void AntiAirTurretTick(float DeltaTime);

	 ATurretPawn* ThisPwan;
	

	 //''' <summary>
		 //''' Returns the angle expressed in radians between -Pi and Pi.
		 //''' </summary>
	 static FORCEINLINE float WrapAngle(float radians)
	 {
		 while( radians < -3.141593f)
		 {
			 radians += 6.283185f;
		 }
		 while (radians > 3.141593f)
		 {
			 radians -= 6.283185f;
		 }
			
		 return radians;
	 }
		
	

	//UPROPERTY(EditAnywhere)
	//	UBoxComponent* Box;

	static FORCEINLINE bool VTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		TArray<FOverlapResult>& HitOut,
		FName TraceChannel = "Pawn"
	){
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
			TraceChannel,
			FCollisionShape::MakeSphere(Radius),
			TraceParams
		);
	}
	inline static bool ConstPredicateHealth(const ABaseCharacter& ip1, const ABaseCharacter& ip2)
	{
		return (ip1.Health < ip2.Health);
	}
};
