// Marius Vlad


#include "SpawnReleaseBlock.h"
#include "ReleaseBlock.h"
#include "Kismet/KismetMathLibrary.h"	//for random in vol
// Sets default values
ASpawnReleaseBlock::ASpawnReleaseBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a Box for the spawn volume.
	whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	whereToSpawn->SetBoxExtent(FVector(1000.0, 500.0, 20.0));
	whereToSpawn->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpawnReleaseBlock::BeginPlay()
{
	for (int i = 0; i < 3; i++)
		spawnAReleaseBlock();

	Super::BeginPlay();
	
}

// Called every frame
void ASpawnReleaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnReleaseBlock::spawnAReleaseBlock() {
	if (GetWorld()) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector spawnLoc = getRandomPtInVolume();
		FRotator rot = FRotator::ZeroRotator;
		GetWorld()->SpawnActor<AReleaseBlock>(releaseBlockClass, spawnLoc, rot, spawnParams);
	}
}

FVector ASpawnReleaseBlock::getRandomPtInVolume() {
	FVector spawnOrigin = whereToSpawn->Bounds.Origin;
	FVector spawnExtent = whereToSpawn->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}
