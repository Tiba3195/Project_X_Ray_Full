// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TPPCharacter.h"
#include "GlobalGameState.h"


//////////////////////////////////////////////////////////////////////////
// ATPPCharacter


UClass* AIControllerClassHolder;
static AGlobalGameState*  BotGS;
ATPPCharacter::ATPPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);	
	//GetCapsuleComponent()->SetupAttachment(RootComponent);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;



	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	


	

}

//////////////////////////////////////////////////////////////////////////
// Input

void ATPPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	
}


// Called every frame
void ATPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Check if the last time we sensed a player is beyond the time out value to prevent bot from endlessly following a player. */
	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut
		&& (GetWorld()->TimeSeconds - LastHeardTime) > SenseTimeOut)
	{
	//	ATopdownCppPlayerController* AIController = Cast<ATopdownCppPlayerController>(GetController());
		if (OurPlayerController)
		{
			bSensedTarget = false;
			/* Reset */
		//	AIController->SetTargetEnemy(nullptr);

			/* Stop playing the hunting sound */
			BroadcastUpdateAudioLoop(false);
		}
	}

	
		//OurPlayerController->SetTargetActor(found);
		OurPlayerController->ReportHealth(Health);

		if ((GetMesh() != nullptr) && (BotGS->Player !=nullptr))
		{
			float d = FVector::Distance(BotGS->Player->GetActorLocation(), GetActorLocation());

			if (d <= BotGS->EnemyDetectionRange && d >= 400)
			{
				GetMesh()->SetRenderCustomDepth(true);
				GetMesh()->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
			}
			else
			{
				GetMesh()->SetRenderCustomDepth(false);
				GetMesh()->CustomDepthStencilValue = 0;
			}
		}
}

// Called when the game starts or when spawned
void ATPPCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE; // or simply assign an int32 within 1-255 range

	OurPlayerController =Cast<ATopdownCppPlayerController>( GetController());
	OurPlayerController->Team = Team;
	OurPlayerController->SetOwner(this);
	UWorld* World = GetWorld();
	//ThisGS = Cast<AGlobalGameState>(World->GetGameState());
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!BotGS->IsValidLowLevel())
		//{
			BotGS = Cast<AGlobalGameState>(World->GetGameState());
			//ThisGS->MainShip = this;
	//	}
	}



	BroadcastUpdateAudioLoop(bSensedTarget);
//	OurPlayerController = GetWorld()->SpawnActor<ATopdownCppPlayerController>(GetActorLocation(), GetActorRotation());
  //  OurPlayerController->SetPawn(this);
}

void ATPPCharacter::Suicide()
{

	BotGS->DecrementBotCount(WasKilledByPlayer);

	Super::Suicide();
}


void ATPPCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATPPCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATPPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);



}
