// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnReleaseBlock.generated.h"

UCLASS()
class WS4_API ASpawnReleaseBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnReleaseBlock();
	UPROPERTY(EditAnywhere)
		UBoxComponent* whereToSpawn;

	FVector getRandomPtInVolume();
	void spawnAReleaseBlock();

	UPROPERTY(EditDefaultsOnly, Category = ReleaseBlock)
		TSubclassOf<class AReleaseBlock> releaseBlockClass;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
