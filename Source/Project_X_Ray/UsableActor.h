// Bass Class For All Usables
#pragma once


#include "GameFramework/Actor.h"
#include "UsableActor.generated.h"

// Different types of useable
UENUM(BlueprintType)
enum class UseableType : uint8 {
	Hardpoint,
	Turret,
	Door,
	Trap,
	Ship,
	None
};


UCLASS()
class PROJECT_X_RAY_API AUsableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableActor();
	AUsableActor(const FObjectInitializer & PCIP);
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//called by the player to avtive as base usable
	UFUNCTION(BlueprintImplementableEvent)
	bool OnUsedPlayer(AMainCharacter* Player);
	//called by the mothership to avtive as base usable
	UFUNCTION(BlueprintImplementableEvent)
	bool OnUsed(AMotherShip* mothership);

	UFUNCTION(BlueprintImplementableEvent)
	bool StartFocusItem();

	UFUNCTION(BlueprintImplementableEvent)
	bool EndFocusItem();

	//runs as command, will be different for each type and implemted in the subclasses
		virtual	void RunCommand(FString command);

		//target for a menu snap on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UArrowComponent* MenuTarget;

	void TurnToFace(AActor* other);
	//The type of useable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UseableType Type = UseableType::None;
	
	
};
