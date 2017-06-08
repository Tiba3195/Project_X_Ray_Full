// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"

#include "DonAINavigation/Private/DonAINavigationPrivatePCH.h"
#include "DonAINavigation/Classes/DonNavigatorInterface.h"
#include "DonAINavigation/Classes/BehaviorTree/BTTask_FlyTo.h"
#include "EnemyShip.h"
#include "FlyingAIController.h"

//UClass* FlyUBehaviorTreeClass;
AFlyingAIController::AFlyingAIController(const FObjectInitializer & PCIP)
	: Super(PCIP)
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


//	static ConstructorHelpers::FClassFinder<UBehaviorTree> BT(TEXT("/Game/BT_FlyTo.BT_FlyTo_C"));
//	if (BT.Class != NULL)
	//{
	//	FlyUBehaviorTreeClass = BT.Class;
	//}

}
// Sets default values
AFlyingAIController::AFlyingAIController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyingAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!NavigationManager)
		NavigationManager = UDonNavigationHelper::DonNavigationManager(this);

//	DynamicCollisionSampler = FDonCollisionSamplerCallback();
	//DynamicCollisionSampler.dy
	//UDonNavigationHelper::
	//auto pawn = GetPawn();
//	auto myMemory = FBT_FlyToTarget();


	// Prepare input:

	//MetaData.ActiveInstanceIdx = GetActiveInstanceIdx();
	//myMemory.Metadata.OwnerComp = this;
	//myMemory.QueryParams = QueryParams;
	//myMemory.QueryParams.CustomDelegatePayload = &myMemory.Metadata;
	//myMemory.bIsANavigator = pawn->GetClass()->ImplementsInterface(UDonNavigator::StaticClass());
	// Bind result notification delegate:
	



}

void AFlyingAIController::TickPathNavigation(float DeltaTime)
{


//	const auto& queryResults = PathData;

	AEnemyShip* pawn =Cast<AEnemyShip>( GetPawn());

	if (pawn != nullptr)
	{

		if (DebugParams.bVisualizePawnAsVoxels)
			NavigationManager->Debug_DrawVoxelCollisionProfile(Cast<UPrimitiveComponent>(pawn->GetRootComponent()));

		FVector flightDirection = PathData.PathSolutionOptimized[solutionTraversalIndex] - pawn->GetActorLocation();

		//auto navigator = Cast<IDonNavigator>(pawn);

		// Add movement input:
		//if (MyMemory->bIsANavigator)
		//{
		// Customized movement handling for advanced users:
		//	IDonNavigator::Execute_AddMovementInputCustom(pawn, flightDirection, 1.f);
		//}
		//else
		//{
		// Default movement (handled by Pawn or Character class)
		pawn->TurnToFace(flightDirection);
		pawn->AddMovementInput(flightDirection, 1.0f);
		//	}

		//UE_LOG(DoNNavigationLog, Verbose, TEXT("Segment %d Distance: %f"), MyMemory->solutionTraversalIndex, flightDirection.Size());

		// Reached next segment:
		if (flightDirection.Size() <= MinimumProximityRequired)
		{
			// Goal reached?
			if (solutionTraversalIndex == PathData.PathSolutionOptimized.Num() - 1)
			{

				// Unregister all dynamic collision listeners. We've completed our task and are no longer interested in listening to these:
				NavigationManager->StopListeningToDynamicCollisionsForPath(DynamicCollisionListener, PathData);
				if (GEngine)
				{
					//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				//	if (bLookingForPath)
					//{
					//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Path End"));
					//}
				}




				//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				pawn->currenttargetindex += 1;
				bLookingForPath = false;
				bHavePath = false;
				return;
			}
			else
			{
				solutionTraversalIndex++;

				// @todo: because we just completed a segment, we should stop listening to collisions on the previous voxel. 
				// If not, a pawn may needlessly recalcualte its solution when a obstacle far behind it intrudes on a voxel it has already visited.

				//	if (MyMemory->bIsANavigator)
				//{
				//if (!MyMemory->Metadata.OwnerComp.IsValid()) // edge case identified during high-speed time dilation. Need to gain a better understanding of exactly what triggers this issue.
				//{
				//	if (pawn->GetController())
				//	{
				//auto blackboard = pawn->GetController()->FindComponentByClass<UBlackboardComponent>();
				//HandleTaskFailure(blackboard);
				//}

				//FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				//}

				if (PathData.PathSolutionOptimized.IsValidIndex(solutionTraversalIndex))
				{
					//bHavePath = false;
					if (GEngine)
					{
						//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
					//	if (bLookingForPath)
					//	{
						//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Follow Path"));
						//}
					}

					//	FVector nextPoint = queryResults.PathSolutionOptimized[solutionTraversalIndex];
					//UE_LOG(DoNNavigationLog, Verbose, TEXT("Segment %d, %s"), MyMemory->solutionTraversalIndex, *nextPoint.ToString());


					//IDonNavigator::Execute_OnNextSegment(pawn, nextPoint);
				}
			}

		}

	}
	

}







void AFlyingAIController::Pathfinding_OnFinish(const FDoNNavigationQueryData& Data)
{


	if (EDonNavigationQueryStatus::InProgress == Data.QueryStatus)
		return;

	switch (Data.QueryStatus)
	{

	case EDonNavigationQueryStatus::Success:

		// Is our path solution no longer valid?
		if (bSolutionInvalidatedByDynamicObstacle)
		{
			//Stackoverflow if this happens after the call to find a new path, so set it there!
			bSolutionInvalidatedByDynamicObstacle = false;
			//

			NavigationManager->StopListeningToDynamicCollisionsForPath(DynamicCollisionListener, Data);
		//	FDoNNavigationResultHandler resultHandler;
		//	resultHandler.BindDynamic(this, &AFlyingAIController::Pathfinding_OnFinish);
		//	DynamicCollisionListener.BindDynamic(this, &AFlyingAIController::Pathfinding_OnDynamicCollisionAlert);

			//AEnemyShip* thispawn = Cast<AEnemyShip>(GetPawn());

		//	bLookingForPath = NavigationManager->SchedulePathfindingTask(GetPawn(), thispawn->TargetPoint[thispawn->currenttargetindex]->GetActorLocation(), QueryParams, DebugParams, resultHandler, DynamicCollisionListener);

			break;
		}

		// Move along the path solution towards our goal:
		//TickPathNavigation(OwnerComp, myMemory, DeltaSeconds);
		if(bLookingForPath) bLookingForPath = false;
		PathData = Data;
		bHavePath = true;
		solutionTraversalIndex = 0;

		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		//	if (bLookingForPath)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Path Found"));
			//}
		}
		break;

    case EDonNavigationQueryStatus::QueryHasNoSolution:

		//FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		NavigationManager->StopListeningToDynamicCollisionsForPath(DynamicCollisionListener, Data);
						bLookingForPath = false;
		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
			//	if (bLookingForPath)
			//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Path QueryHasNoSolution"));
			//}
		}
		break;

	case EDonNavigationQueryStatus::TimedOut:

		// For advanced usecases we could support partial path traversal, etc (so we slowly progress towards the goal
		// with each cycle of query-timeout->partial-reschedule->partial-navigate->query-timeout->partial-reschedule, etc)
		// but for now, let's just keep things simple.
		NavigationManager->StopListeningToDynamicCollisionsForPath(DynamicCollisionListener, Data);
		//FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		bLookingForPath = false;
		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
			//	if (bLookingForPath)
			//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Path TimedOut"));
			//}
		}
		break;

	case EDonNavigationQueryStatus::Failure:

	//	auto pawn = GetPawn();
	//	auto blackboard = pawn ? pawn->GetController()->FindComponentByClass<UBlackboardComponent>() : NULL;

		//if (blackboard)
		//	HandleTaskFailure(blackboard);

		//FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		NavigationManager->StopListeningToDynamicCollisionsForPath(DynamicCollisionListener, Data);
		bLookingForPath = false;
		if (GEngine)
		{
			//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
			//	if (bLookingForPath)
			//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Path Failure"));
			//}
		}
		break;
	}



}

void AFlyingAIController::Pathfinding_OnDynamicCollisionAlert(const FDonNavigationDynamicCollisionPayload& Data)
{
	bSolutionInvalidatedByDynamicObstacle = true;
}

// Called every frame
void AFlyingAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bHavePath)
	{
		TickPathNavigation(DeltaTime);
		return;
	}

	AEnemyShip* thispawn = Cast<AEnemyShip>(GetPawn());


	if (thispawn != nullptr && bLookingForPath)
	{
	
				if (thispawn->currenttargetindex >= thispawn->TargetPoint.Num())
				{
					if (DontLoop)
					{
						bLookingForPath = false;
						thispawn->AtTarget = true;
					}					
					thispawn->currenttargetindex = 0;								

				}
				if (thispawn->TargetPoint.Num() > 0 )
				{
					if (thispawn->TargetPoint[thispawn->currenttargetindex])
					{


						FVector flightDirection = thispawn->TargetPoint[thispawn->currenttargetindex]->GetActorLocation() - thispawn->GetActorLocation();

						thispawn->TurnToFace(flightDirection);
						thispawn->AddMovementInput(flightDirection, 1.0f);


						if (FVector::Distance(GetPawn()->GetActorLocation(), thispawn->TargetPoint[thispawn->currenttargetindex]->GetActorLocation()) <= 100)
						{
							thispawn->currenttargetindex += 1;
						}

						if (GEngine)
						{
							//	// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
							if (bLookingForPath)
							{
								//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Looking For Path"));
							}
						}
					}
				}
	
				
			//}
	//	}
	}
	// Schedule task:
	// This gets called when an actor begins to overlap with the current trigger volume
}

void AFlyingAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (DynamicCollisionListener.IsBound())
	{
	DynamicCollisionListener.Unbind();
	}	



	Super::EndPlay(EndPlayReason);
}