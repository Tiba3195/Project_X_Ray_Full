// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "SelectionRoseActor.h"

ASelectionRoseActor::ASelectionRoseActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Forward->SetupAttachment(RootComponent);
	Slots = TArray<USelectionRoseSlotComponent*>();

	BackGround = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BackGround"));
	BackGround->SetupAttachment(Forward);

	FloaterIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Selection Icon"));
	FloaterIcon->SetupAttachment(BackGround);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TExt"));
	Text->SetupAttachment(BackGround);

	DamageAmountlbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageAmount lbl"));
	DamageAmountlbl->SetupAttachment(BackGround);

	Rangelbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Range lbl"));
	Rangelbl->SetupAttachment(BackGround);

	FireRatelbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Fire Rate lbl"));
	FireRatelbl->SetupAttachment(BackGround);


	Accuracylbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Acuaccuracy lbl"));
	Accuracylbl->SetupAttachment(BackGround);



	DamageAmountText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageAmount Text"));
	DamageAmountText->SetupAttachment(BackGround);


	RangeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Range Text"));
	RangeText->SetupAttachment(BackGround);


	FireRateText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Fire Rate Text"));
	FireRateText->SetupAttachment(BackGround);


	AccuracyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Accuracy Text"));
	AccuracyText->SetupAttachment(BackGround);


}
// Sets default values
ASelectionRoseActor::ASelectionRoseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Forward->SetupAttachment(RootComponent);
	Slots = TArray<USelectionRoseSlotComponent*>();

	BackGround = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BackGround"));
	BackGround->SetupAttachment(Forward);

	FloaterIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Selection Icon"));
	FloaterIcon->SetupAttachment(BackGround);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TExt"));
	Text->SetupAttachment(BackGround);

	DamageAmountlbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageAmount lbl"));
	DamageAmountlbl->SetupAttachment(BackGround);

	Rangelbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Range lbl"));
	Rangelbl->SetupAttachment(BackGround);

	FireRatelbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Fire Rate lbl"));
	FireRatelbl->SetupAttachment(BackGround);


	Accuracylbl = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Acuaccuracy lbl"));
	Accuracylbl->SetupAttachment(BackGround);



	DamageAmountText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageAmount Text"));
	DamageAmountText->SetupAttachment(BackGround);


	RangeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Range Text"));
	RangeText->SetupAttachment(BackGround);


	FireRateText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Fire Rate Text"));
	FireRateText->SetupAttachment(BackGround);


	AccuracyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Accuracy Text"));
	AccuracyText->SetupAttachment(BackGround);







}

// Called when the game starts or when spawned
void ASelectionRoseActor::BeginPlay()
{
	Super::BeginPlay();
		   for (UActorComponent* hit : GetComponents())
		   {
			   USelectionRoseSlotComponent* tester = Cast<USelectionRoseSlotComponent>(hit);
			   if (tester != nullptr)
			   {
				   Slots.Add(tester);
			   }
		   }	

}

void ASelectionRoseActor::SetUseable(AUsableActor * useable)
{
	if (this == nullptr)
		return;
	CurrentActor = useable;
}

void ASelectionRoseActor::ClearUsable()
{
	if (this == nullptr)
		return;
	CurrentActor = nullptr;
}

// Called every frame
void ASelectionRoseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);


	if (PC != nullptr)
	{
		float LocationX;
		float LocationY;
		FVector camLoc;
		FRotator camRot;
		PC->GetMousePosition(LocationX, LocationY);
		FVector2D MousePosition(LocationX, LocationY);
		FVector2D ViewPos(0, 0);

		Text->SetVisibility(false);
		FloaterIcon->SetVisibility(false);
		//BackGround->ToggleVisibility(true)

		for (USelectionRoseSlotComponent* hit : Slots)
		{
		   hit->SetSprite(Inactive);
		   switch (hit->Tier)
		   {
		   case Tier::one:
			   hit->TierText->SetSprite(T1Icon);
			   break;
		   case Tier::two:
			   hit->TierText->SetSprite(T2Icon);
			   break;

		   case Tier::three:
			   hit->TierText->SetSprite(T3Icon);
			   break;
		   }

		   switch (hit->Type)
		   {
		   case TurretType::AA:
			   hit->TypeText->SetSprite(AAIcon);
			   break;
		   case TurretType::Ground:
			   hit->TypeText->SetSprite(GroundIcon);
			   break;

		   case TurretType::Util:
			   hit->TypeText->SetSprite(UtilIcon);
			   break;
		   }
		}

		// Do a trace and see if there the position intersects something in the world  
		for (USelectionRoseSlotComponent* hit : Slots)
		{					

			if (CurrentActor != nullptr)
			{
				PC->ProjectWorldLocationToScreen(hit->GetComponentLocation(), ViewPos);
				float d = FVector::Distance(FVector(ViewPos.X, 0, ViewPos.Y), FVector(MousePosition.X, 0, MousePosition.Y));
				if (d <= 55)
				{
					Text->SetText(hit->Text);
					Text->SetVisibility(true);

					DamageAmountText->SetText(hit->DamageAmount);
					RangeText->SetText(hit->Range);
					FireRateText->SetText(hit->FireRate);
					AccuracyText->SetText(hit->Accuracy);

					FloaterIcon->SetVisibility(true);
					FloaterIcon->SetSprite(hit->SelectedIcon);
					hit->SetSprite(ActiveSprite);
				
					if (PC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
					{
						if (hit->Command != "")
						{
							CurrentActor->RunCommand(hit->Command);
						}
					}

					break;

			}

			}		
		}
	}
}

