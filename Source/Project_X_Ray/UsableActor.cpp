// Bass Class For All Usables

#include "Project_X_Ray.h"
#include "UsableActor.h"



AUsableActor::AUsableActor()
{
 
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MenuTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("MenuTarget"));
	MenuTarget->SetupAttachment(RootComponent);

}
AUsableActor::AUsableActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MenuTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("MenuTarget"));
	MenuTarget->SetupAttachment(RootComponent);
}
// Called when the game starts or when spawned
void AUsableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUsableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUsableActor::RunCommand(FString command)
{
}
//turns the menu target to the player
void AUsableActor::TurnToFace(AActor* other)
{
	FVector Direction = other->GetActorLocation() - GetActorLocation();
	FRotator NewControlRotation = Direction.Rotation();
	
	NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
	MenuTarget->SetRelativeRotation(FRotator(0.0f, NewControlRotation.Yaw, 0.0f));
}
