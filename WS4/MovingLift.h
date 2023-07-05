// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingLift.generated.h"

UCLASS()
class WS4_API AMovingLift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingLift();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	    float runningTime;
	UPROPERTY(EditAnywhere)
	    float amplitude;
	UPROPERTY(EditAnywhere)
	    float speed;
	FVector liftLocation;
};
