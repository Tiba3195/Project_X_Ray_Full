// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "ProjectileFireControlComponent.h"


// Sets default values for this component's properties
UProjectileFireControlComponent::UProjectileFireControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileFireControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProjectileFireControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileFireControlComponent::Fire(UArrowComponent* Muzzle, AActor* Owner, bool IsBot)
{

	// Bug here, projectile offset is funky and moves -+X depending on the camera rot, needs to be fixed!!
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{	

		FVector CameraLocation;
		FRotator CameraRotation;
		//Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FRotator MuzzleRotation = Muzzle->GetComponentRotation();
		// Skew the aim to be slightly upwards.
		if (!IsBot)
		{
		//	MuzzleRotation.Pitch += 5.0f;
		}
		
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Owner;
			//SpawnParams.Instigator = Owner;
			// Spawn the projectile at the muzzle.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, Muzzle->GetSocketLocation("Muzzle"), MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->MuzzleOffset = Muzzle;
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}

}
void UProjectileFireControlComponent::Fire(TArray<UArrowComponent*> Muzzle, AActor* Owner, bool IsBot, FRotator direction)
{
	// Bug here, projectile offset is funky and moves -+X depending on the camera rot, needs to be fixed!!
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		for (UArrowComponent* muzzle : Muzzle)
		{

			//FVector CameraLocation;
			//FRotator CameraRotation;
			//Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);
			//FRotator MuzzleRotation = muzzle->GetComponentRotation();
			// Skew the aim to be slightly upwards.
			if (!IsBot)
			{
				//	MuzzleRotation.Pitch += 5.0f;
			}

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Owner;
				//SpawnParams.Instigator = Owner;
				// Spawn the projectile at the muzzle.
				AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, muzzle->GetComponentLocation(), direction, SpawnParams);
				if (Projectile)
				{
					Projectile->MuzzleOffset = muzzle;
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = direction.Vector();
					Projectile->FireInDirection(LaunchDirection);
				}
			}
		}

	}

}




void UProjectileFireControlComponent::Fire(TArray<UArrowComponent*> Muzzle, AActor* Owner, bool IsBot)
{

	// Bug here, projectile offset is funky and moves -+X depending on the camera rot, needs to be fixed!!
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		for (UArrowComponent* muzzle : Muzzle)
		{

			//FVector CameraLocation;
			//FRotator CameraRotation;
			//Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);
			FRotator MuzzleRotation = muzzle->GetComponentRotation();
			// Skew the aim to be slightly upwards.
			if (!IsBot)
			{
				//	MuzzleRotation.Pitch += 5.0f;
			}

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Owner;
				//SpawnParams.Instigator = Owner;
				// Spawn the projectile at the muzzle.
				AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, muzzle->GetComponentLocation(), MuzzleRotation, SpawnParams);
				if (Projectile)
				{
					Projectile->MuzzleOffset = muzzle;
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
				}
			}
		}

		}


	

}