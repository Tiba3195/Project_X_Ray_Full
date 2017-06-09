// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Project_X_Ray.h"
#include "TPPCharacter.h"
#include "TopdownCppPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "GlobalGameState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TurretActor.h"
#include "BaseTrapActor.h"


static AGlobalGameState* CurrentGS;

ATopdownCppPlayerController::ATopdownCppPlayerController(const FObjectInitializer & PCIP)
	: Super(PCIP)
{
	//PCIP.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"));

	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));

	//Create a Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1500.f;
	Sight->PeripheralVisionAngleDegrees = 130.f;

	//Tell the sight sense to detect everything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	//Register the sight sense to our Perception Component
	AIPerceptionComponent->ConfigureSense(*Sight);



}


ATopdownCppPlayerController::ATopdownCppPlayerController()
{

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));

	//Create a Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1500.f;
	Sight->PeripheralVisionAngleDegrees = 130.f;

	//Tell the sight sense to detect everything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	//Register the sight sense to our Perception Component
	AIPerceptionComponent->ConfigureSense(*Sight);
}

void ATopdownCppPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		ABaseCharacter* thisowner = Cast<ABaseCharacter>(GetOwner());

		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		TArray<FOverlapResult> HitOut;


		scantime += DeltaTime;
		if (scantime >= 0.3f)
		{
				if (VTraceSphere(this, CameraLocation, CameraLocation + DetectionRange, DetectionRange, HitOut) == true)
			{
				for (FOverlapResult hit : HitOut)
				{
					AActor* tester = hit.GetActor();

					bool ischaracter = tester->IsA<ABaseCharacter>();
					if (ischaracter)
					{
						ABaseCharacter* foundcharacter = Cast<ABaseCharacter>(tester);
						if (foundcharacter->Team != Team)
						{
							found = foundcharacter;
							//	GetCharacterMovement()->StopMovementImmediately();
							SetTargetActor(found);
							HaveTarget = true;
							break;
						}
					}
					bool isturret = tester->IsA<ATurretActor>();
					if (isturret)
					{
							found = tester;
							//	GetCharacterMovement()->StopMovementImmediately();
							SetTargetActor(found);
							HaveTarget = true;
							break;
					}
					bool istrap = tester->IsA<ABaseTrapActor>();
					if (istrap)
					{
							found = tester;
							//	GetCharacterMovement()->StopMovementImmediately();
							SetTargetActor(found);
							HaveTarget = true;
							break;
					}
				}
			}
			scantime = 0;
		}


		if (!HaveTarget)
		{
			found = nullptr;
			thisowner->HaveTarget = HaveTarget;
		}

		if (found != nullptr && HaveTarget)
		{
			float d = FVector::Distance(found->GetActorLocation(), GetOwner()->GetActorLocation());
			if (d >= DetectionRange + 200)
			{
				found = nullptr;
				HaveTarget = false;
				//	GetCharacterMovement()->StopMovementImmediately();
			}
			else
			{

					
					//TurnToFace(found);
					if (thisowner->CurrentFireRate >= thisowner->FireRate)
					{
						thisowner->HaveTarget = HaveTarget;
						//FVector MuzzleLocation = MuzzleOffset->GetSocketLocation("Muzzle");
						// Get the camera transform.
						if (thisowner->CurrentWeapon != NULL)
						{
							thisowner->CurrentWeapon->Fire(thisowner, true);
						}

						thisowner->CurrentFireRate = 0;
					}				
			}
		}
	
		//MoveToMouseCursor();	

}

void ATopdownCppPlayerController::MoveToMouseCursor()
{
	if(this)
	{
		APawn* const MyPawn = GetPawn();

		if (MyPawn != nullptr)
		{
			if (CurrentGS)
			{
				if (IsValid(MyPawn))
				{
					UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
					float const Distance = FVector::Dist(CurrentGS->Player->GetActorLocation(), MyPawn->GetActorLocation());

					// We need to issue move command only if far enough in order for walk animation to play correctly
					if (NavSys)
					{
						//NavSys->find
					//	NavSys->SimpleMoveToLocation(this, CurrentGS->Player->GetActorLocation());
					}
				}
			}
		}
	
	}	
}

void ATopdownCppPlayerController::SetTargetActor(AActor * target)
{
	BlackboardComp->SetValueAsObject(BlackboardEnemyKey, target);
}

void ATopdownCppPlayerController::ReportHealth(float health)
{
	BlackboardComp->SetValueAsFloat(BlackboardHealthKey, health);
}


void ATopdownCppPlayerController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	//If our character exists inside the UpdatedActors array, register him
	//to our blackboard component

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor->IsA<ABaseCharacter>())
		{
			ABaseCharacter* other = Cast<ABaseCharacter>(Actor);
			if (other->Team == 0)
			{
				BlackboardComp->SetValueAsObject(BlackboardEnemyKey, other);
				return;
			}		
		}
	}

	//The character doesn't exist in our updated actors - so make sure
	//to delete any previous reference of him from the blackboard
	BlackboardComp->SetValueAsObject(BlackboardEnemyKey, nullptr);
}

void ATopdownCppPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (BehaviorTree)
	{
		//Initialize the Blackboard and start the attached behavior tree
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}

	//Register the OnPerceptionUpdated function to fire whenever the AIPerception get's updated
	//AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATopdownCppPlayerController::OnPerceptionUpdated);
}

AActor* ATopdownCppPlayerController::GetSeeingPawn()
{
	//Return the seeing pawn
	UObject* object = BlackboardComp->GetValueAsObject(BlackboardEnemyKey);

	return object ? Cast<AActor>(object) : nullptr;
}

void ATopdownCppPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		CurrentGS = Cast<AGlobalGameState>(World->GetGameState());
	}
}


void ATopdownCppPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	
}

void ATopdownCppPlayerController::SetTargetEnemy(ABaseCharacter * pawn)
{
}


