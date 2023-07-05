// Marius Vlad


#include "MovingLift.h"

// Sets default values
AMovingLift::AMovingLift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	runningTime = 0.0f;
	amplitude = 100.0f; 
	speed = 1.0f;
}

// Called when the game starts or when spawned
void AMovingLift::BeginPlay()
{
	Super::BeginPlay();
	liftLocation = GetActorLocation(); //platformLocation in my case
}

// Called every frame
void AMovingLift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	runningTime += DeltaTime;
	float height = FMath::Sin(runningTime * speed) * amplitude; //horizontalDistance in my case
	SetActorLocation(liftLocation + FVector(height, 0.0f, 0.0f));
}

