// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "SelectionRoseSlotComponent.h"
#include "UsableActor.h"
#include "SelectionRoseActor.generated.h"

UCLASS()
class PROJECT_X_RAY_API ASelectionRoseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectionRoseActor();
	ASelectionRoseActor(const class FObjectInitializer& PCIP);

	void SetUseable(AUsableActor* useable);
	void ClearUsable();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<USelectionRoseSlotComponent*> Slots;


	float MaxDamageAmount = 0;

	float MaxRange = 0;

	float MaxFireRate = 0;

	float MaxAcuaccuracy = 0;

	AUsableActor* CurrentActor;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSpriteComponent* FloaterIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSpriteComponent* BackGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* ActiveSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* Inactive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<UPaperSprite*> SlotIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* BackGroundSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* T3Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* T2Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* T1Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* AAIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* GroundIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UPaperSprite* UtilIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UArrowComponent* Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* DamageAmountlbl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* Rangelbl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* FireRatelbl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* Accuracylbl;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* DamageAmountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* RangeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* FireRateText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTextRenderComponent* AccuracyText;
	
};
