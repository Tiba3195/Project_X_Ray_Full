// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GridNodeActor.h"
#include "GridManagerActor.generated.h"


//You dont necessarily need this Data Unit struct if your fundamental data type is simple like float or FString.
USTRUCT(BlueprintType)
struct FGridNodeHolder
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
		AGridNodeActor* GridNode;

	FGridNodeHolder()
	{	
		
	}
};

USTRUCT(BlueprintType)
struct FDataRow
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
		TArray<FGridNodeHolder> Cols;
	FDataRow() {}
};

USTRUCT(BlueprintType)
struct F2DDataArray
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
		TArray<FDataRow> Rows;
	F2DDataArray() {}
};





UCLASS(BlueprintType)
class PROJECT_X_RAY_API AGridManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManagerActor();
	AGridManagerActor(const class FObjectInitializer& PCIP);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		F2DDataArray Grid;
	
};
