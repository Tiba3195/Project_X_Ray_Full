// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemyShip.h"
#include "TurretActor.h"
#include "FlyingAIController.h"


AEnemyShip::AEnemyShip(const FObjectInitializer & PCIP)
	: Super(PCIP)
{
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
RootComponent = SphereComponent;
	//SphereComponent->SetupAttachment(RootComponent);
	//GetMovementComponent()->InitializeComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	ShipForward = CreateDefaultSubobject<UArrowComponent>(TEXT("Ship Arrow Attachment"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(SphereComponent);
	ShipForward->SetupAttachment(SphereComponent);

	Mesh->SetupAttachment(ShipForward);
	Gun->SetupAttachment(Forward);

	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<UArrowComponent*>();





//	SphereComponent->SetupAttachment(Forward);
}
// Sets default values
AEnemyShip::AEnemyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
		RootComponent = SphereComponent;
//	SphereComponent->SetupAttachment(RootComponent);
	//GetMovementComponent()->InitializeComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	ShipForward = CreateDefaultSubobject<UArrowComponent>(TEXT("Ship Arrow Attachment"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(SphereComponent);
	ShipForward->SetupAttachment(SphereComponent);

	Mesh->SetupAttachment(ShipForward);
	Gun->SetupAttachment(Forward);

	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<UArrowComponent*>();

}

void AEnemyShip::AddMovement(FVector WorldDirection, float ScaleValue, bool bForce /*=false*/)
{
	if (WorldDirection.Size() > 0)
	{
		//TurnToFace(WorldDirection);

	

		if (MovementComponent)
		{
		//	SphereComponent->ad
			MovementComponent->AddInputVector(WorldDirection * ScaleValue, false);
			//MovementComponent->ConsumeInputVector();
		}
	}
}

void AEnemyShip::TurnToFace(FVector Direction)
{
	FRotator NewControlRotation = Direction.Rotation();
	NewControlRotation.Roll = 0;
	NewControlRotation.Pitch = 0;
	ShipForward->SetWorldRotation(NewControlRotation);
}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//found = nullptr;
	CurrentFireRate += DeltaTime;

	TArray<FOverlapResult> HitOut;
	//TArray<ABaseCharacter*> ListtoSort = TArray<ABaseCharacter*>();
	ATurretActor*	found = nullptr;
	// Find objects in range
	if (VTraceSphere(this, GetActorLocation(), GetActorLocation() + AttackRange, AttackRange, HitOut) == true)
	{
		// Filter objects in range
		for (FOverlapResult hit : HitOut)
		{
			found = Cast<ATurretActor>(hit.GetActor());
			if (found)
			{
				TurnToFace(found);
			//	if (!found->bDead && !found->bIsDying && found->Team != 0)
				//{
					//ListtoSort.Add(found);
			//	}
				break;
			}
			else
			{
				found = nullptr;
			}
		}

	//	ListtoSort.Sort(ConstPredicate);

	}

	if (CurrentFireRate >= FireRate)
	{
		if (found != nullptr)
		{
			if (ProjectileFireControlComponent)
			{
				//FVector MuzzleLocation = MuzzleOffset->GetSocketLocation("Muzzle");
				// Get the camera transform.
				if (MuzzleOffsets.Num() > 0)
				{
					ProjectileFireControlComponent->Fire(MuzzleOffsets, this, true, Forward->GetComponentRotation());
				}

			}
		}	
		CurrentFireRate = 0;
	}
}

// Called to bind functionality to input
void AEnemyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemyShip::AddMuzzleOffSet(UArrowComponent * MuzzleOffset)
{

	MuzzleOffset->SetupAttachment(Forward);

	MuzzleOffsets.Add(MuzzleOffset);
}

void AEnemyShip::TurnToFace(AActor* other)
{
	FVector Direction = other->GetActorLocation()- GetActorLocation();
	FRotator NewControlRotation = Direction.Rotation();

	//NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
	//NewControlRotation.Roll = FRotator::ClampAxis(NewControlRotation.Roll);
	//NewControlRotation.Pitch = FRotator::ClampAxis(NewControlRotation.Pitch);
	NewControlRotation.Roll = 0;
	Forward->SetWorldRotation(NewControlRotation);
}

float AEnemyShip::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		Health = FMath::Max(0.0f, Health);

		if (Health <= 0)
		{
			SetActorTickEnabled(false);
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{

			PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}

		//	MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
	}

	return 0.0f;
}

bool AEnemyShip::Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
{

	FTimerHandle TimerHandle;

	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyShip::Suicide, 2.0f, false);
	return true;
}

void AEnemyShip::Suicide()
{
	DestroyConstructedComponents();
	Destroy();

}

void AEnemyShip::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser)
{
	//if (DamageEffect)
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(this, DamageEffect, Hit.ImpactPoint, GetActorRotation());
	//}
}