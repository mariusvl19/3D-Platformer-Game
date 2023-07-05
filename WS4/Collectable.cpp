// Marius Vlad


#include "Collectable.h"
#include "Components/SphereComponent.h"
#include "WS4Character.h"
#include "Kismet/GameplayStatics.h"  //for PlaySoundAtLocation


// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("collisionComponent"));
	RootComponent = collisionComponent;
	collisionComponent->SetSimulatePhysics(true);
	collisionComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	value = 1;

}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	collisionComponent->OnComponentHit.AddDynamic(this, &ACollectable::OnHit);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectable::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AWS4Character* chr = Cast<AWS4Character>(OtherActor);
	if (chr) {
		if (collectSound)
			UGameplayStatics::PlaySoundAtLocation(this, collectSound, GetActorLocation());
		chr->onGrab(this, HitComp);
		chr->health -= value;
	}
}


