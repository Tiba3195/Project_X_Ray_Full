// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DonAINavigation/Classes/DonNavigationHelper.h"
#include "FlyingAIController.generated.h"




USTRUCT()
struct FBT_FlyToTarget_DebugParamsEX : public FDoNNavigationDebugParams
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DoN Navigation")
		bool bVisualizePawnAsVoxels;
};

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AFlyingAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AFlyingAIController();
	AFlyingAIController(const FObjectInitializer & PCIP);


void	EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere)
		UBehaviorTree*  FlyingBTree;

	UPROPERTY(EditAnywhere)
		bool  DontLoop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DoN Navigation")
		float MinimumProximityRequired = 15.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DoN Navigation")
		FDoNNavigationQueryParams QueryParams;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DoN Navigation")
		FBT_FlyToTarget_DebugParamsEX DebugParams;

	UFUNCTION(BlueprintCallable, Category = "DoN Navigation")
	void Pathfinding_OnFinish(const FDoNNavigationQueryData& Data);

	UFUNCTION(BlueprintCallable, Category = "DoN Navigation")
	void Pathfinding_OnDynamicCollisionAlert(const FDonNavigationDynamicCollisionPayload& Data);

	UPROPERTY(EditAnywhere, Category = "DoN Navigation")
		ADonNavigationManager* NavigationManager;

	FDonNavigationDynamicCollisionDelegate DynamicCollisionListener;

	bool bSolutionInvalidatedByDynamicObstacle;

	bool bHavePath;
	bool bLookingForPath = true;
	int solutionTraversalIndex;

	UPROPERTY(EditAnywhere, Category = "DoN Navigation")
	FDoNNavigationQueryData PathData;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TickPathNavigation(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
