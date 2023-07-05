// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class WS4_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
		class UAIPerceptionComponent* aiPercComp;
	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
		class UAISenseConfig_Sight* sightConfig;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		FVector baseLoc;
	UPROPERTY(BlueprintReadWrite, Category = Movement)
		FVector currVel;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		float speed;
	UPROPERTY(EditAnywhere, Category = Enemy)
		float radius;
	    float distSq;	//for back to base calcs
	    bool backToBase;

	UFUNCTION()
		void OnSensed(const TArray<AActor*>& testActors);

	void setNewRotation(FVector targPos, FVector currPos);

	UPROPERTY(VisibleAnywhere, Category = Movement)
		FRotator enemyRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float rotationSpeed;
	bool interpRotation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
