// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "PlayerHUDComponent.h"




UPlayerHUDComponent::UPlayerHUDComponent(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{


}

// Sets default values
UPlayerHUDComponent::UPlayerHUDComponent()
	: Super()
{


}

bool UPlayerHUDComponent::SetSprite(class UPaperSprite* NewSprite)
{
	return Super::SetSprite(NewSprite);
}