// Marius Vlad


#include "GoalArea.h"
#include "Collectable.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" //for sound
#include "WS4Character.h"

// Sets default values
AGoalArea::AGoalArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("collisionComponent"));
	RootComponent = collisionComponent;
	collisionComponent->SetSimulatePhysics(false);
	collisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void AGoalArea::BeginPlay()
{
	Super::BeginPlay();
	collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoalArea::OnBeginOverlap);
}

// Called every frame
void AGoalArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ACollectable* c = Cast<ACollectable>(OtherActor);
	if (c) {
		if (winningSound) //try and play the sound, if specified
			UGameplayStatics::PlaySoundAtLocation(this, winningSound, GetActorLocation());
		AWS4Character* chr = Cast<AWS4Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (chr)
			chr->UIMessage = "You won!";

	}
}
