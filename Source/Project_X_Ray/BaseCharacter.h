// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ProjectileFireControlComponent.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "PlayerWeapon.h"
#include "BaseCharacter.generated.h"



UCLASS()
class PROJECT_X_RAY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:


	// Sets default values for this character's properties
	ABaseCharacter();
	ABaseCharacter(const class FObjectInitializer& PCIP);

	ABaseCharacter* found;

	/* Last time the player was spotted */
	float LastSeenTime;

	/* Last time the player was heard */
	float LastHeardTime;

	/* Last time we attacked something */
	float LastMeleeAttackTime;

	/* Time-out value to clear the sensed position of the player. Should be higher than Sense interval in the PawnSense component not never miss sense ticks. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SenseTimeOut;

	/* Resets after sense time-out to avoid unnecessary clearing of target each tick */
	bool bSensedTarget;
	float scantime = 0;

	/** animation played on death */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HaveTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bInRagdoll = false;

	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bIsDying = false;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Health=0;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MaxHealth=0;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Stamina = 0;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MaxStamina = 0;
	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bDead = false;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PatrolLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotTypeKeyName;

	float BaseRunSpeed = 0;
	//Check to see if its shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool IsShooting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float bAimPitch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	APlayerWeapon* CurrentWeapon;
	
	bool IsAlive = false;

	/* Update the vocal loop of the zombie (idle, wandering, hunting) */
	UFUNCTION(Reliable, NetMulticast)
		void BroadcastUpdateAudioLoop(bool bNewSensedTarget);

	void BroadcastUpdateAudioLoop_Implementation(bool bNewSensedTarget);

	UAudioComponent* PlayCharacterSound(USoundCue* CueToPlay);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SoundPlayerNoticed;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SoundHunting;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SoundIdle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SoundWandering;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SoundAttackMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perseption)
		UPawnNoiseEmitterComponent*  PawnNoiseEmitter;

	bool IsActive = false;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		float FireRate = 3;

	 float CurrentFireRate=0;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UProjectileFireControlComponent* ProjectileFireControlComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Pawn suicide */
	virtual void Suicide();

	/** Kill this pawn */
	virtual void KilledBy(class APawn* EventInstigator);

	/** Returns True if the pawn can die in the current state */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;


	/**
	* Kills pawn.  Server/authority only.
	* @param KillingDamage - Damage amount of the killing blow
	* @param DamageEvent - Damage event of the killing blow
	* @param Killer - Who killed this pawn
	* @param DamageCauser - the Actor that directly caused the damage (i.e. the Projectile that exploded, the Weapon that fired, etc)
	* @returns true if allowed
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);



	/** play effects on hit */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	/** switch to ragdoll */
	void SetRagdollPhysics();

	void StopAllAnimMontages();

	/** play anim montage */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/** stop playing montage */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;
	/** animation played on death */
	UPROPERTY(EditAnywhere)
		float DetectionRange = 256;


	UPROPERTY(EditAnywhere)
		bool IsBot=false;

	void TurnToFace(AActor* other);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** animation played on death */
	UPROPERTY(EditAnywhere)
		int Team = 0;
	

	/** animation played on death */
	UPROPERTY(EditAnywhere, Category = Animation)
		UAnimMontage* DeathAnim;

	bool WasKilledByPlayer = false;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

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
	//	TraceParams.bTraceAsyncScene = true;
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

	

};
