// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "PlayerHUDComponent.generated.h"


UENUM(BlueprintType)
enum class HUDItemType : uint8 {
	Panel,
	Button	
};
UENUM(BlueprintType)
enum class ButtonActionType : uint8 {
	Show,
	Hide,
	Toggle,
	None
};
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_X_RAY_API UPlayerHUDComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
	
public:

	UPlayerHUDComponent();
	UPlayerHUDComponent(const FObjectInitializer & PCIP);

	bool SetSprite(class UPaperSprite* NewSprite) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UPaperSprite* ActiveIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UPaperSprite* InactiveIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FString Command = "";	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	HUDItemType Type = HUDItemType::Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	ButtonActionType ActionType = ButtonActionType::None;

	

};
