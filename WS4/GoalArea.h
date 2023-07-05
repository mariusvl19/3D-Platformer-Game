// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalArea.generated.h"

UCLASS()
class WS4_API AGoalArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalArea();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* winningSound;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
