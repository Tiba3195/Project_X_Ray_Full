// turret will snap to this and all building will also be done with the object

#pragma once


#include "UsableActor.h"
#include "TurretAttachmenttComponent.h"
#include "TurretComponent.h"
#include "TurretActor.h"
#include "MediumTurretActor.h"
#include "LightTurretActor.h"
#include "HeavyTurretActor.h"
#include "HardPointAttachment.h"
#include "TurretHardPoint.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ATurretHardPoint : public AUsableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretHardPoint();
	ATurretHardPoint(const FObjectInitializer & PCIP);

	void RegisterDelegate();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//test method builds the base turret actor
	 void BuildTurret();
	 //method builds based on the string that was passes into this object
	 void BuildTurret(FString TurretName);
	//helps to stop bulding many turrets on one hardpoint
	 bool HasTurret;
	 //basemesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UStaticMeshComponent* HardpointBase;
	//the turret will snap to this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTurretAttachmenttComponent* TurretAttachment;
	//this will snap the hardpoint to the place you want(used as an offset) 90% chance of being removed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UHardPointAttachment* HardPointAttachment;
	//runs the command, we implemnt runcommand method here
	 void RunCommand(FString command) override;
	//Sets the Camera Rotation
	UPROPERTY(EditAnywhere)
		FVector AttachmentOffset = FVector(0.0f, 0.0f, 0.0f);
	//Index of this hardpoint, helps with looks for menu snapping and running commands
		int HardPointIndex =-1;

	
};
