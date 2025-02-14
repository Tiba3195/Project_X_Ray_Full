// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
//#include "GameFramework/PlayerController.h"
#include "ControlPointActor.h"
#include "BaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Runtime/AIModule/Classes/Navigation/CrowdManager.h"
#include "TopdownCppPlayerController.generated.h"


UCLASS()
class ATopdownCppPlayerController : public AAIController
{
	GENERATED_BODY()
private:
	/** The function that fires when the perception of our AI gets updated */
	UFUNCTION()
		void OnPerceptionUpdated(TArray<AActor*> UpdatedActors);

	/** BlackboardComponent - used to initialize blackboard values and set/get values from a blackboard asset */
	UBlackboardComponent* BlackboardComp;

	/** BehaviorTreeComponent - used to start a behavior tree */
	UBehaviorTreeComponent* BehaviorTreeComp;

	/** Blackboard Key Value Name */
	const FName BlackboardEnemyKey = FName("Enemy");
	/** Blackboard Key Value Name */
	const FName BlackboardHealthKey = FName("Health");
	/** Blackboard Key Value Name */
	const FName BlackboardDamagerKey = FName("Damager");
	/** Blackboard Key Value Name */
	const FName BlackboardShouldFindCPKey = FName("ShouldFindCP");	

	/** A Sight Sense config for our AI */
	UAISenseConfig_Sight* Sight;
	/** A Sight Sense config for our AI */
	UAISenseConfig_Hearing* Hearing;

	AActor* found;

	float scantime = 0;



//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HaveTarget = false;
	

public:
	ATopdownCppPlayerController(const FObjectInitializer& PCIP);
	ATopdownCppPlayerController();

	AControlPointActor* CurrentTarget;

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	void SetTargetActor(AActor* target);
	void ReportHealth(float health);
	void SetTargetEnemy(ABaseCharacter* pawn);
	void SetDamager(AActor* target);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float DetectionRange = 256;


	float Team = -1.0f;


	
	/** The Perception Component of our AI */
	UPROPERTY(VisibleAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent;


	virtual void Possess(APawn* InPawn) override;

	/** Returns the seeing pawn. Returns null, if our AI has no target */
	AActor* GetSeeingPawn();
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


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;
	
	// End PlayerController interface


	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** The Behavior Tree that contains the logic of our AI */
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	
};

