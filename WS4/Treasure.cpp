// Marius Vlad


#include "Treasure.h"
#include "WS4Character.h"

// Sets default values
ATreasure::ATreasure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("collisionComponent"));
	RootComponent = collisionComponent;
	collisionComponent->SetSimulatePhysics(true);
	collisionComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void ATreasure::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AWS4Character* chr = Cast<AWS4Character>(OtherActor);
	if (chr) {
	//	if (collectSound)
		//	UGameplayStatics::PlaySoundAtLocation(this, collectSound, GetActorLocation());
		chr->onGrab(this, HitComp);
		//chr->health -= value;
	}
}

// Called when the game starts or when spawned
void ATreasure::BeginPlay()
{
	Super::BeginPlay();
	collisionComponent->OnComponentHit.AddDynamic(this, &ATreasure::OnHit);
}

// Called every frame
void ATreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

