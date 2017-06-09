// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "BaseCharacter.h"


ABaseCharacter::ABaseCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = Health;
	




}

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = Health;
	


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	WasKilledByPlayer = false;
	BaseRunSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	CurrentFireRate += DeltaTime;
}




void ABaseCharacter::BroadcastUpdateAudioLoop_Implementation(bool bNewSensedTarget)
{
}

UAudioComponent * ABaseCharacter::PlayCharacterSound(USoundCue * CueToPlay)
{
	return nullptr;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		Health = FMath::Max(0.0f, Health);

		if (Health <= 0)
		{		
			ABaseCharacter* found = Cast<ABaseCharacter>(DamageCauser->GetOwner());
			if (found != nullptr)
			{
				if (found->Team != Team)
				{
					WasKilledByPlayer = true;
				}
			}
		//	
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

void ABaseCharacter::Suicide()
{

	if (bIsDying && bInRagdoll)
	{
	//We have to do this here or we end up with garbage!			
		DetachFromControllerPendingDestroy();
		DestroyPlayerInputComponent();
		SetActorHiddenInGame(true);
		SetLifeSpan(2.0f);
		DestroyConstructedComponents();
		RemoveFromRoot();
		bDead = true;	
		Destroy();
	}
}

void ABaseCharacter::KilledBy(APawn * EventInstigator)
{
}

bool ABaseCharacter::CanDie(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser) const
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
// Animations

float ABaseCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void ABaseCharacter::StopAnimMontage(class UAnimMontage* AnimMontage)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOut.GetBlendTime(), AnimMontage);
	}
}

void ABaseCharacter::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}

bool ABaseCharacter::Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
{
	if (IsBot)
	{
		IsAlive = false;
		//DetachFromControllerPendingDestroy();
		StopAllAnimMontages();

		if (GetMesh())
		{
			static FName CollisionProfileName(TEXT("Ragdoll"));
			GetMesh()->SetCollisionProfileName(CollisionProfileName);
		}
		SetActorEnableCollision(true);
		GetCharacterMovement()->StopMovementImmediately();
		bIsDying = true;
		// Death anim
		float DeathAnimDuration = PlayAnimMontage(DeathAnim);

		// Ragdoll
		if (DeathAnimDuration > 0.f)
		{
			// Trigger ragdoll a little before the animation early so the character doesn't
			// blend back to its normal position.
			const float TriggerRagdollTime = DeathAnimDuration - 1.5f;

			// Enable blend physics so the bones are properly blending against the montage.
			GetMesh()->bBlendPhysics = true;

			// Use a local timer handle as we don't need to store it for later but we don't need to look for something to clear
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::SetRagdollPhysics, FMath::Max(0.1f, TriggerRagdollTime), false);
		}
		else
		{
			SetRagdollPhysics();
		}

		//	SetRagdollPhysics();

		// disable collisions on capsule
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	
	return false;
}

void ABaseCharacter::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser)
{
}

void ABaseCharacter::SetRagdollPhysics()
{
	// bInRagdoll = false;

	if (IsPendingKill())
	{
		bInRagdoll = false;
	}
	else if (!GetMesh() || !GetMesh()->GetPhysicsAsset())
	{
		bInRagdoll = false;
	}
	else
	{
		// initialize physics/etc
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
		bInRagdoll = true;
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);

	if (!bInRagdoll)
	{
		// hide and set short lifespan
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(1.0f);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::Suicide, FMath::Max(0.1f, 0.2f), false);
	}
	else
	{

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::Suicide, FMath::Max(0.1f, 10.0f), false);
	}

}





void ABaseCharacter::TurnToFace(AActor* other)
{

		FVector Direction =(other->GetActorLocation() - FVector(0,0,25)) - GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();	
		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
		bAimPitch = NewControlRotation.Pitch;
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0.0f, NewControlRotation.Yaw , 0.0f));
	
}
