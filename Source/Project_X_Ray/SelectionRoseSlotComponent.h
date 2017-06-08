// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "SelectionRoseSlotComponent.generated.h"



UENUM(BlueprintType)
enum class TurretType : uint8 {
	AA,
	Ground,
	Util,
	None
};

UENUM(BlueprintType)
enum class Tier : uint8 {
	one,
	two,
	three
};

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_X_RAY_API USelectionRoseSlotComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	

public: 
	USelectionRoseSlotComponent();
	USelectionRoseSlotComponent(const FObjectInitializer & PCIP);

	bool SetSprite(class UPaperSprite* NewSprite) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString toolTip="";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString Text ="";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString DamageAmount= "0";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString Range= "0";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString FireRate= "0";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString Accuracy = "0";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TurretType Type = TurretType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		Tier Tier = Tier::one;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* SelectedIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString Command = "";	

		UPaperSpriteComponent* TierText;
		UPaperSpriteComponent* TypeText;	

};
