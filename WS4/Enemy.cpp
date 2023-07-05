// Marius Vlad


#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"	
#include "Perception/AISenseConfig_Sight.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currVel = FVector::ZeroVector;
	speed = 30.0f;
	radius = 500.0f;
	distSq = BIG_NUMBER; //use defined big num	
	backToBase = false;

	// AI Perception settings
	aiPercComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("aiPercComponent"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = radius;
	sightConfig->LoseSightRadius = radius + 100.0f;
	sightConfig->PeripheralVisionAngleDegrees = 90.0f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	sightConfig->SetMaxAge(0.5f);
	aiPercComp->ConfigureSense(*sightConfig);
	aiPercComp->SetDominantSense(sightConfig->GetSenseImplementation());
	aiPercComp->OnPerceptionUpdated.AddDynamic(this, &AEnemy::OnSensed);

	interpRotation = false;
	rotationSpeed = 1.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	FVector playerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector newD = playerLoc - GetActorLocation();// diff: pawn and Enemy loc
	newD.Z = 0.0f;	//we are NOT interested in any Z diff
	FRotator rotDir = newD.Rotation() - GetActorForwardVector().Rotation();	//calc diff in reqd dir & curr. dir
	rotDir.Normalize();	//ensure rotation is a unit vector
	SetActorRotation(rotDir);
	//draw a debug line to check it goes from Enemy to Pawn in 'new' dir
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() 
		           * 2000.0f, FColor::Red, true, 5.0f, 0, 1.0f);
	baseLoc = GetActorLocation();
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Handle movement based on where Enemy is to baseLoc
	if (!currVel.IsZero()) {
		FVector newLocation = GetActorLocation() + currVel * DeltaTime;
		if (backToBase) {
			if ((newLocation - baseLoc).SizeSquared2D() < distSq)
				distSq = (newLocation - baseLoc).SizeSquared2D();
			else {	//if dist bigger, stop
				currVel = FVector::ZeroVector;
				distSq = BIG_NUMBER;
				backToBase = false;
			}
		}
		SetActorLocation(newLocation);
	}

	if (interpRotation) {
		FRotator oldR = GetActorForwardVector().Rotation();
		oldR.Roll = oldR.Pitch = 0.0f; //only allow rotation about Z (Yaw)
		FRotator nr = FMath::RInterpTo(oldR, enemyRotator, DeltaTime, rotationSpeed);
		if ((nr - enemyRotator).IsNearlyZero()) {
			nr = enemyRotator;
			interpRotation = false;
		}
		SetActorRotation(nr);
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnSensed(const TArray<AActor*>& testActors) {
	for (int i = 0; i < testActors.Num(); i++) {
		FString n = testActors[i]->GetName();
		FActorPerceptionBlueprintInfo info;
		aiPercComp->GetActorsPerception(testActors[i], info);
		interpRotation = true;
		if (info.LastSensedStimuli[0].WasSuccessfullySensed()) {
			FVector dir = testActors[i]->GetActorLocation() - GetActorLocation();
			dir.Z = 0.0f;	//reset as they may be at diff Z values
			currVel = dir.GetSafeNormal() * speed; //set vel towards actor
			setNewRotation(testActors[i]->GetActorLocation(), GetActorLocation());
		}
		else 
		{	//actor has moved away from radius
			FVector dir = baseLoc - GetActorLocation();
			dir.Z = 0.0f;	//reset as they may be at diff Z values
			setNewRotation(baseLoc, GetActorLocation());
			if (dir.SizeSquared2D() > 1.0f) 
			{	//set vel towards baseLoc
				currVel = dir.GetSafeNormal() * speed;
				backToBase = true;
			}
		}
	}
}

void AEnemy::setNewRotation(FVector targPos, FVector currPos) {
	FVector newD = targPos - currPos;	//diff in curr loc and Enemy loc
	newD.Z = 0.0f;	//we are NOT interested in any Z diff
	enemyRotator = newD.Rotation();
	if (interpRotation)
		enemyRotator = newD.Rotation();
	else
		SetActorRotation(newD.Rotation()); //rotation with NO interp

}
