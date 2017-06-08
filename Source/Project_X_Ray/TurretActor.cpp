// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretActor.h"




ATurretActor::ATurretActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	//This was a super sucky bug, took me hrs to find out the correct way to do this!!
	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);

	Base->SetupAttachment(TurretAttachment);

	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(Base);
	Gun->SetupAttachment(Forward);

	ThisPwan = CreateDefaultSubobject<ATurretPawn>(TEXT("Turret Pawn"));


	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<UArrowComponent*>();
	DamageEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Damage Effect"));
	//DamageEffect->SetupAttachment(Base);
	DethEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Deth Effect"));
	//DethEffect->SetupAttachment(Base);
	MaxHealth = Health;



}

// Sets default values
ATurretActor::ATurretActor()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	//This was a super sucky bug, took me hrs to find out the correct way to do this!!
	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);

	Base->SetupAttachment(TurretAttachment);

	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(Base);
	Gun->SetupAttachment(Forward);


	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<UArrowComponent*>();

	ThisPwan = CreateDefaultSubobject<ATurretPawn>(TEXT("Turret Pawn"));

	DamageEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Damage Effect"));
	//DamageEffect->SetupAttachment(Base);
	DethEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Deth Effect"));
	//DethEffect->SetupAttachment(Base);
	MaxHealth = Health;


}

float ATurretActor::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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

bool ATurretActor::Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
{
	
	FTimerHandle TimerHandle;

		if (DethEffect != nullptr)
		{	
			UGameplayStatics::SpawnEmitterAtLocation(this, DethEffect, GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), GetActorRotation(),true);
		}	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurretActor::Suicide, 2.0f, false);
	return true;
}

void ATurretActor::Suicide()
{
	DestroyConstructedComponents();
	Destroy();
	
}

void ATurretActor::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser)
{
	//if (DamageEffect)
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(this, DamageEffect, Hit.ImpactPoint, GetActorRotation());
	//}
}

void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
}

void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTurretActiveCounter += DeltaTime;

	if (DamageEffect != nullptr)
	{
		if  (CurrentTurretActiveCounter >= 1.0f)
		{
			if (Health <= MinHealth)
			{
				//DamageEffect->SetWorldLocation(GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(this, DamageEffect, GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), GetActorRotation(), true);
			}	
			
			CurrentTurretActiveCounter = 0;
		}
	}

	if (!IsAntiAir)
	{
		GroundTurretTick(DeltaTime);
	}
	else
	{
		AntiAirTurretTick(DeltaTime);
	}	
}
void ATurretActor::GroundTurretTick(float DeltaTime)
{

	TArray<FOverlapResult> HitOut;
	TArray<ATPPCharacter*> ListtoSort = TArray<ATPPCharacter*>();

	// Find objects in range
	if (VTraceSphere(this, GetActorLocation(), GetActorLocation() + AttackRange, AttackRange, HitOut) == true)
	{
		// Filter objects in range
		for (FOverlapResult hit : HitOut)
		{
			found = Cast<ATPPCharacter>(hit.GetActor());
			if (found)
			{
				if (!found->bDead && !found->bIsDying )
				{
					if(found->Team != 0) ListtoSort.Add(found);
				}
			}
			else
			{
				found = nullptr;
			}
		}

		ListtoSort.Sort(ConstPredicateHealth);

		if (ListtoSort.Num() > 0)
		{
			found = nullptr;
			found = ListtoSort[0];
		}
	}

	if (found != nullptr)
	{
		if (!found->bDead && !found->bIsDying)
		{
			FVector target = found->GetActorLocation();
			float d = FVector::Distance(target, GetActorLocation());
			if (d >= AttackRange + 200)
			{
				found = nullptr;
			}
			else
			{
				TurnToFace(found, DeltaTime);

				if (CurrentFireRate >= FireRate)
				{
					if (ProjectileFireControlComponent)
					{
						//FVector MuzzleLocation = MuzzleOffset->GetSocketLocation("Muzzle");
						// Get the camera transform.
						if (MuzzleOffsets.Num() > 0 && CanFire)
						{
							ProjectileFireControlComponent->mode = TurretFireMode;
							ProjectileFireControlComponent->Fire(MuzzleOffsets, this, true);
						}

					}
					CurrentFireRate = 0;
				}
			}
		}
	}

	CurrentFireRate += DeltaTime;


}
void ATurretActor::AntiAirTurretTick(float DeltaTime)
{

	TArray<FOverlapResult> HitOut;
	//TArray<AEnemyShip*> ListtoSort = TArray<AEnemyShip*>();






	// Find objects in range
	if (MuzzleOffsets.Num() > 0)
	{


	
	if (VTraceSphere(this, MuzzleOffsets[0]->GetComponentLocation() , GetActorLocation() + AttackRange, AttackRange, HitOut,"Vehicle") == true)
	{
		// Filter objects in range
		for (FOverlapResult hit : HitOut)
		{
			AntiAirfound = Cast<AEnemyShip>(hit.GetActor());
			if (AntiAirfound)
			{
				
					//ListtoSort.Add(AntiAirfound);
					break;
			}
			else
			{
				AntiAirfound = nullptr;
			}
		}

	//	ListtoSort.Sort(ConstPredicate);

		//if (ListtoSort.Num() > 0)
		//{
		//	AntiAirfound = nullptr;
			//AntiAirfound = ListtoSort[0];
		//}
	}

	if (AntiAirfound != nullptr)
	{
		
			FVector target = AntiAirfound->GetActorLocation();
			float d = FVector::Distance(target, GetActorLocation());
			if (d >= AttackRange + 200)
			{
				AntiAirfound = nullptr;
			}
			else
			{
				TurnToFace(AntiAirfound, DeltaTime);

				if (CurrentFireRate >= FireRate)
				{
					if (ProjectileFireControlComponent)
					{
						//FVector MuzzleLocation = MuzzleOffset->GetSocketLocation("Muzzle");
						// Get the camera transform.
						if ((MuzzleOffsets.Num() > 0) && CanFire)
						{
							//if (MuzzleFlash)
							//{
							//MuzzleFlash->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
							//MuzzleFlash->Activate();

								//UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, GetActorLocation(), GetActorRotation());

						//	}
							ProjectileFireControlComponent->Fire(MuzzleOffsets, this, true);
						}

					}
					CurrentFireRate = 0;
				}
			
		}
	}
	CurrentFireRate += DeltaTime;
}
	



}
void ATurretActor::RegisterDelegate()
{
	
	//if (Box != nullptr)
	//{
	//	if (!Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
	//	{
		
	//		Box->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginBoxOverlap);
	//	}
	//}
}

void ATurretActor::TurnToFace(AActor* other, float DeltaTime)
{
	FVector Direction = other->GetActorLocation() - GetActorLocation();
	FRotator NewControlRotation = Direction.Rotation();
	

	float diff = FRotator::NormalizeAxis(NewControlRotation.Yaw - Forward->GetComponentRotation().Yaw);
	if ((diff <= 15.0f) && (diff >= -15.0f))
	{
		CanFire = true;
	}
	else 
	{
		CanFire = false;
	}
	NewControlRotation.Normalize();

	Forward->SetWorldRotation(FMath::RInterpConstantTo(Forward->GetComponentRotation(), NewControlRotation, DeltaTime, TurnSpeed));

	
}

void ATurretActor::AddMuzzleOffSet(UArrowComponent * MuzzleOffset)
{


	MuzzleOffset->SetupAttachment(Gun);
	MuzzleOffsets.Add(MuzzleOffset);
}

void ATurretActor::OnBeginTriggerOverlap(AActor* OverlappedActor ,AActor* OtherActor)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
	//	TurnToFace(OtherActor);
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}
void ATurretActor::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}

void ATurretActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	//if (Box != nullptr)
	//{
	//	if (Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
	//	{
		//	Box->OnComponentBeginOverlap.RemoveDynamic(this, &ATurretActor::OnBeginBoxOverlap);
		//}
	//}
	Super::EndPlay(EndPlayReason);
}
