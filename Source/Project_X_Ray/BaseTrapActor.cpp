// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "BaseTrapActor.h"
#include "BaseCharacter.h"



ABaseTrapActor::ABaseTrapActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	SquishedCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Squished Cube"));


	SquishedCube->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);
	
}

// Sets default values
ABaseTrapActor::ABaseTrapActor()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;



	SquishedCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Squished Cube"));


	SquishedCube->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);

}

void ABaseTrapActor::BeginPlay()
{
	Super::BeginPlay();

	IsEffect = false;

	if (TriggerBox != nullptr)
	{
		if (!TriggerBox->OnComponentBeginOverlap.IsAlreadyBound(this, &ABaseTrapActor::OnBeginBoxOverlap))
		{
			TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrapActor::OnBeginBoxOverlap);
		}

		if (!TriggerBox->OnComponentEndOverlap.IsAlreadyBound(this, &ABaseTrapActor::EndOverlap))
		{
			TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrapActor::EndOverlap);
		}
	}

}


void ABaseTrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TrapEffect != nullptr)
	{
		if (!IsEffect)
		{ 
		
			//DamageEffect->SetWorldLocation(GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(this, TrapEffect, GetActorLocation() + FVector(0.0f, 0.0f, EffectHeightOffset), GetActorRotation(), true);
			IsEffect = true;
			CurrentFrameDelta = 0;
		}
		

			
				CurrentFrameDelta += DeltaTime;
		
	}

}

void ABaseTrapActor::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{




}

void ABaseTrapActor::EndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{


}

void ABaseTrapActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TriggerBox != nullptr)
	{
		if (TriggerBox->OnComponentBeginOverlap.IsAlreadyBound(this, &ABaseTrapActor::OnBeginBoxOverlap))
		{
			TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseTrapActor::OnBeginBoxOverlap);
		}

		if (TriggerBox->OnComponentEndOverlap.IsAlreadyBound(this, &ABaseTrapActor::EndOverlap))
		{
			TriggerBox->OnComponentEndOverlap.RemoveDynamic(this, &ABaseTrapActor::EndOverlap);
		}
	}

	Super::EndPlay(EndPlayReason);
}


	