// Fill out your copyright notice in the Description page of Project Settings.
// <--------------------------------------INFO---------------------------------------->
/*

Anything with a ***The Rage*** = more kittens harmming!

Need to check if this is ok to call all the time        Controller = UGameplayStatics::GetPlayerController(this, 0);

This class will control the first person stuff, movment, shooting, pickups and anthing that has to do with the first person player.

This mother fucker! run physics with no controller make sure to tick the box if you use a pawn with our camera set up, will save you hrs!

Time 3:11am time for bed, last thing added selectable turrets! well boxes but they will be turrets!

*/
// <-------------------------------------END INFO------------------------------------->

#include "Project_X_Ray.h"
#include "FPSProjectile.h"
#include "MainCharacter.h"
#include "UsableActor.h"
#include "GlobalGameState.h"
#include "IngameHUD.h"


INT32 Counter = 0;
INT32 FireCounter = 0;
//static AGlobalGameState* GS;
UClass* SelectionroseClassHolder;
UClass* HUDClassHolder;
AGlobalGameState* PlayerGS;
AMainCharacter::AMainCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
//	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FirstPersonCameraOffset + BaseEyeHeight);

	// Allow the pawn to control camera rotation.
	OurCamera->bUsePawnControlRotation = true;
	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(OurCamera);


	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	//SEt Shadows
	FPSMesh->CastShadow = false;
	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);
	//Set Use Disyance
	MaxUseDistance = 300;
	//Set Focus
	bHasNewFocus = true;

	//FP_Gun->RelativeScale3D.X
	PawnNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));


	static ConstructorHelpers::FClassFinder<ASelectionRoseActor> TheRose(TEXT("/Game/BP_SelectionRoseActor.BP_SelectionRoseActor_C"));
	if (TheRose.Class != NULL)
	{
		SelectionroseClassHolder = TheRose.Class;


	}

	MenuTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("MenuTarget"));
	MenuTarget->SetupAttachment(OurCamera);	

	//CurrentWeapon = CreateDefaultSubobject<APlayerWeapon>(TEXT("Current Weapon"));

	//static ConstructorHelpers::FClassFinder<class UWidget> THewidget(TEXT("/Game/RadarSystem/Widgets/UMG_RadarWidget.UMG_RadarWidget_C"));
	//if (THewidget.Class != NULL)
	//{

  // }
	static ConstructorHelpers::FClassFinder<APlayerHUD> TheHUD(TEXT("/Game/BP_MainHUD3.BP_MainHUD3_C"));
	if (TheHUD.Class != NULL)
	{
		HUDClassHolder = TheHUD.Class;
     }
	//UWidget* MiniMapWidget;

}




// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FirstPersonCameraOffset + BaseEyeHeight);

	// Allow the pawn to control camera rotation.
	OurCamera->bUsePawnControlRotation = true;
	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(OurCamera);


	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	//SEt Shadows
	FPSMesh->CastShadow = false;
	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);
	//Set Use Disyance
	MaxUseDistance = 300;
	//Set Focus
	bHasNewFocus = true;

	//FP_Gun->RelativeScale3D.X
	PawnNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));

	static ConstructorHelpers::FClassFinder<ASelectionRoseActor> TheRose(TEXT("/Game/BP_SelectionRoseActor.BP_SelectionRoseActor_C"));
	if (TheRose.Class != NULL)
	{
		SelectionroseClassHolder = TheRose.Class;


	}

	MenuTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("MenuTarget"));
	MenuTarget->SetupAttachment(OurCamera);

	static ConstructorHelpers::FClassFinder<class UWidget> THewidget(TEXT("/Game/RadarSystem/Widgets/UMG_RadarWidget.UMG_RadarWidget_C"));
	if (THewidget.Class != NULL)
	{

	}
	static ConstructorHelpers::FClassFinder<APlayerHUD> TheHUD(TEXT("/Game/BP_MainHUD3.BP_MainHUD3_C"));
	if (TheHUD.Class != NULL)
	{
		HUDClassHolder = TheHUD.Class;
	}

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	IsAlive = true;
	
	UWorld* World = GetWorld();
	if (World)
	{
		PlayerGS = Cast<AGlobalGameState>(World->GetGameState());
		if (PlayerGS)
		{
			PlayerGS->Player = this;
		}
		FActorSpawnParameters SpawnParams;
	//	FAttachmentTransformRules AttaRules;
		if (SelectionroseClassHolder != nullptr)
		{
			
		}
		if (HUDClassHolder != nullptr)
		{
			MainHUD = World->SpawnActor<APlayerHUD>(HUDClassHolder, MenuTarget->GetComponentLocation(), MenuTarget->GetComponentRotation(), SpawnParams);
			MainHUD->AttachRootComponentTo(MenuTarget,NAME_None,EAttachLocation::SnapToTarget,true);
			
			Selectionrose = Cast<ASelectionRoseActor>(MainHUD->SelectionRoseComp->GetChildActor()); // World->SpawnActor<ASelectionRoseActor>(SelectionroseClassHolder, GetActorLocation() + FVector(0.0f, 0.0f, 100), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			Selectionrose->DisableComponentsSimulatePhysics();
			Selectionrose->SetActorEnableCollision(false);

		}
	}

	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));		
	}






}
void AMainCharacter::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{




}

void AMainCharacter::EndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{






}

void AMainCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{


		Super::EndPlay(EndPlayReason);
}
// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (IsActive)
	{
		//MainHUD->SetActorLocation(MenuTarget->GetComponentLocation());
		//MainHUD->SetActorRotation(MenuTarget->GetComponentRotation());
	
		Counter += 1;
		//this is reall bad, can do much better!
		if (Counter >= 3)
		{
			CheckInView();
			Counter = 0;
		}
	}





	if (Controller && Controller->IsLocalController())
	{
		AUsableActor* usable = GetUsableInView();
		// End Focus
		if (FocusedUsableActor != usable)
		{
			if (FocusedUsableActor)
			{
				FocusedUsableActor->EndFocusItem();
			}
			bHasNewFocus = true;
		}
		// Assign new Focus
		FocusedUsableActor = usable;
		// Start Focus.
		if (usable)
		{
			if (bHasNewFocus)
			{
				usable->StartFocusItem();
				bHasNewFocus = false;
			}
		}
	}
}
// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AMainCharacter::Use);
//	PlayerInputComponent->BindAction("ClearSelection", IE_Pressed, this, &AMainCharacter::ClearSelection);
	//***The Rage***
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInputEX);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInputEX);
	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJump);
	//Fire!!
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);

	PlayerInputComponent->BindAction("ShowMenu", IE_Pressed, this, &AMainCharacter::ShowMenu);

	PlayerInputComponent->BindAction("ThirdPersonMode", IE_Pressed, this, &AMainCharacter::SwitchToMotherShip);

	// Set up "movement" bindings.
}
void AMainCharacter::ShowMenu()
{
	UWorld* World = GetWorld();

	if (World)
	{
	
		PlayerGS->showMenu();

		if (FPSMesh->IsVisible())
		{
			FPSMesh->ToggleVisibility(true);
		}
		else
		{
			FPSMesh->ToggleVisibility(true);
		}
	}

}
void AMainCharacter::SwitchToMotherShip()
{
	UWorld* World = GetWorld();

	if (World)
	{
		
		PlayerGS->MainShip->BeginTakeControl();
	}
}
void AMainCharacter::AddControllerPitchInputEX(float Val)
{
	if (Val != 0.f)
	{
		APlayerController* const PC = UGameplayStatics::GetPlayerController(this, 0);

		//OurCamera->SetWorldRotation(FRotator(OurCamera->GetComponentRotation().YawVal, 0, 0));
		PC->AddPitchInput(Val);
	}
}

void AMainCharacter::AddControllerYawInputEX(float Val)
{
	if (Val != 0.f)
	{
		APlayerController* const PC = UGameplayStatics::GetPlayerController(this, 0);
		PC->AddYawInput(Val);
	}
}

void AMainCharacter::MoveForward(float Value)
{
	    //Gets the current PlayerController and checks for null
	   Controller  = UGameplayStatics::GetPlayerController(this, PlayerID);
		if (Controller)
		{
			// Find out which way is "forward" and record that the player wants to move that way.
			FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
}
void AMainCharacter::MoveRight(float Value)
{
	//Gets the current PlayerController and checks for null
	Controller = UGameplayStatics::GetPlayerController(this, PlayerID);
		if (Controller)
		{
			// Find out which way is "right" and record that the player wants to move that way.
			FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}	
}
void AMainCharacter::StartJump()
{	
		bPressedJump = true;	
}
void AMainCharacter::StopJump()
{	
		bPressedJump = false;
}
void AMainCharacter::Fire()
{


	if (!IsShooting && !PlayerGS->MenuOpen)
	{	
		IsShooting = true;
		FireCounter = 0;
//		ProjectileFireControlComponent->Fire(MuzzleOffset, this, IsBot);
		if (CurrentWeapon != NULL)
		{
		
			CurrentWeapon->Fire(this, IsBot);
		}
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::StopShooting, 0.128f, false);
	}			
				
}
void AMainCharacter::StopShooting()
{
	IsShooting = false;
}
/*
Performs raytrace to find closest looked-at UsableActor.
*/

ATurretActor* CheckUseableEX(AActor* actor, bool Onclick)
{
	ATurretActor* ClickedPawn = Cast<ATurretActor>(actor);

	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
			// Unposses ourselves  
			//playerController->UnPossess();
			// Posses the controller we clicked on  
			//playerController->Possess(ClickedPawn);
			return ClickedPawn;
		}
		else
		{
			AIngameHUD::UsableInView();
			return ClickedPawn;
		}
	}
	return nullptr;
}
ATurretHardPoint* CheckTurretHardpointEX(AActor* actor, bool Onclick)
{
	ATurretHardPoint* ClickedPawn = Cast<ATurretHardPoint>(actor);

	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
			// Unposses ourselves  
			//playerController->UnPossess();
			// Posses the controller we clicked on  
			//playerController->Possess(ClickedPawn);
			return ClickedPawn;
		}
		else
		{
			AIngameHUD::HardPointInView();
			return ClickedPawn;
		}
	}
	return nullptr;
}

AUsableActor* AMainCharacter::GetUsableInView()
{
	FVector camLoc;
	FRotator camRot;
	Controller = UGameplayStatics::GetPlayerController(this, PlayerID);
	if (Controller == NULL)
		return NULL;

	Controller->GetPlayerViewPoint(camLoc, camRot);
	const FVector start_trace = camLoc;
	const FVector direction = camRot.Vector();
	const FVector end_trace = start_trace + (direction * MaxUseDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, start_trace, end_trace, COLLISION_PROJECTILE, TraceParams);


	return Cast<AUsableActor>(Hit.GetActor());
}
/*
Runs on Server. Perform "OnUsed" on currently viewed UsableActor if implemented.
*/
void AMainCharacter::Use()
{
	AUsableActor* usable = GetUsableInView();
	if (usable)
	{
		usable->OnUsedPlayer(this);
	}
}
void AMainCharacter::CheckInView()
{

		FVector camLoc;
		FRotator camRot;
		Controller = UGameplayStatics::GetPlayerController(this, PlayerID);
		if (Controller == NULL)
			return;

		Controller->GetPlayerViewPoint(camLoc, camRot);
		const FVector start_trace = camLoc;
		const FVector direction = camRot.Vector();
		const FVector end_trace = start_trace + (direction * MaxUseDistance);

		FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;

		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, start_trace, end_trace, COLLISION_PROJECTILE, TraceParams) == true)
		{
			bool HasHit = false;
			AUsableActor* UsableINSight = Cast<AUsableActor>(HitResult.GetActor());
			// If the actor we intersected with is a controller posses it  
			//AUsableActor* ClickedPawn = Cast<AUsableActor>(HitResult.GetActor());
			if (UsableINSight != nullptr)
			{
				switch (UsableINSight->Type)
				{
				case UseableType::Hardpoint:

					Selectionrose->SetActorHiddenInGame(false);
					UsableINSight->TurnToFace(this);
					//Selectionrose->SetActorLocation(UsableINSight->MenuTarget->GetComponentLocation());
					//Selectionrose->SetActorRotation(UsableINSight->MenuTarget->GetComponentRotation());
					Selectionrose->SetUseable(UsableINSight);
					break;
				case UseableType::Turret:
				
					break;
		
				}			
			}
		
		}
		else
		{
			Selectionrose->ClearUsable();
			AIngameHUD::NoUsableInView();
			AIngameHUD::NoHardPointInView();
			Selectionrose->SetActorHiddenInGame(true);
		}
}

