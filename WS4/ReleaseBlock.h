// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "ReleaseBlock.generated.h"

UCLASS()
class WS4_API AReleaseBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReleaseBlock();
	static int numberOfBlocksHit;

	// Treasure class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Treasure)
		TSubclassOf<class ATreasure> treasureClass;


	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UCapsuleComponent* collisionComponent;// Capsule collision comp
	UStaticMeshComponent* staticMeshComponent;
	UMaterialInstanceDynamic* dynMaterial1;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isHit = false;

};
