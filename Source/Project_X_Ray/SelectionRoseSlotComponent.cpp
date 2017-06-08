// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "SelectionRoseSlotComponent.h"


USelectionRoseSlotComponent::USelectionRoseSlotComponent(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
	TierText = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Tier"));
	TierText->SetupAttachment(this);
	TierText->SetRelativeLocation(FVector(0.0f, -3.0f, 65.0f));
	TierText->SetTranslucentSortPriority(2);

	TypeText = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Type"));
	TypeText->SetupAttachment(this);
	TypeText->SetRelativeLocation(FVector(0.0f, -3.0f, -65.0f));
	TypeText->SetTranslucentSortPriority(3);
}

// Sets default values
USelectionRoseSlotComponent::USelectionRoseSlotComponent()
	: Super()
{
	//PrimaryActorTick.bCanEverTick = true;
	TierText = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Tier"));
	TierText->SetupAttachment(this);
	TierText->SetRelativeLocation(FVector(0.0f, -3.0f, 65.0f));
	TierText->SetTranslucentSortPriority(2);

	TypeText = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Type"));
	TypeText->SetupAttachment(this);
	TypeText->SetRelativeLocation(FVector(0.0f, -3.0f, -65.0f));
	TypeText->SetTranslucentSortPriority(3);
}

bool USelectionRoseSlotComponent::SetSprite(class UPaperSprite* NewSprite)
{
	return Super::SetSprite(NewSprite);
}