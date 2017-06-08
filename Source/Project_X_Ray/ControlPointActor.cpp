// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "ControlPointActor.h"
#include "GlobalGameState.h"


// Sets default values
AControlPointActor::AControlPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	CPMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CP Mesh"));
	CPMesh->SetupAttachment(RootComponent);
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship VisibleComponent"));
	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//CameraOne->SetupAttachment(RootComponent);
	//CameraOne->SetRelativeLocation(CameraOffset);
	//CameraOne->SetRelativeRotation(CameraRotation);

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AControlPointActor::BeginPlay()
{
	Super::BeginPlay();
	AGlobalGameState* GS;
	UWorld* World = GetWorld();
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!GS)
		//	{
		GS = Cast<AGlobalGameState>(World->GetGameState());		
		GS->AddControlPoint(this);
		//	}
	}
	
}

// Called every frame
void AControlPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FOverlapResult> HitOut;
//	TArray<ABaseCharacter*> ListtoSort = TArray<ABaseCharacter*>();
	CurrentNumberOfEnemys = 0;
	// Find objects in range
	if (VTraceSphere(this, GetActorLocation(), GetActorLocation() + 300, 300, HitOut) == true)
	{
		// Filter objects in range
		for (FOverlapResult hit : HitOut)
		{
			APawn* found = Cast<APawn>(hit.GetActor());
			if (found != nullptr)
			{
				CurrentNumberOfEnemys += 1;
			}

		}
	}
	

	if (CurrentNumberOfEnemys >= NumberOfEnemyToTakeControl)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AControlPointActor::TakeControl, 2.0f, false);
		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
			
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Control Point Under Attack!"));
			
		}
	}	

}

void AControlPointActor::TakeControl()
{
	if (CurrentNumberOfEnemys >= NumberOfEnemyToTakeControl)
	{
		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Control Point Lost"));

		}

	}
}

