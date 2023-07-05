// Marius Vlad


#include "ReleaseBlock.h"
#include "Treasure.h"
#include "Collectable.h"

int AReleaseBlock::numberOfBlocksHit = 0;
// Sets default values
AReleaseBlock::AReleaseBlock()
{
	isHit = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	float cRad = 20.0f, hh = 50.0f;
	collisionComponent->InitCapsuleSize(cRad, hh);
	collisionComponent->SetSimulatePhysics(true);
	collisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = collisionComponent;

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComponent"));
	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/BasicShapes/Cube")));
	if (meshToUse) {
		staticMeshComponent->SetStaticMesh(meshToUse);
		static ConstructorHelpers::FObjectFinder <UMaterial>materialBlue(TEXT("MaterialInstanceConstant'/Engine/EditorMaterials/WidgetMaterial_Z'"));
		UMaterialInstanceDynamic* dynMaterial = UMaterialInstanceDynamic::Create(materialBlue.Object, NULL);
		staticMeshComponent->SetMaterial(0, dynMaterial);
		FVector minB, maxB;
		staticMeshComponent->GetLocalBounds(minB, maxB);
		float scaleXY = cRad / minB.X;
		float scaleZ = hh / minB.Z;
		staticMeshComponent->SetWorldScale3D(FVector(scaleXY, scaleXY, scaleZ));
		staticMeshComponent->SetCollisionProfileName("NoCollision");
		staticMeshComponent->SetupAttachment(RootComponent);
	}
	//FObjectFinder has to be in a constructor!
	static ConstructorHelpers::FObjectFinder <UMaterial>material(TEXT("MaterialInstanceConstant'/Engine/EditorMaterials/WidgetMaterial_X'"));
	dynMaterial1 = UMaterialInstanceDynamic::Create(material.Object, NULL);

}

// Called when the game starts or when spawned
void AReleaseBlock::BeginPlay()
{
	Super::BeginPlay();
	collisionComponent->OnComponentHit.AddDynamic(this, &AReleaseBlock::OnHit);
}

// Called every frame
void AReleaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReleaseBlock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	
	ACollectable* c = Cast<ACollectable>(OtherActor);
	if (c && !isHit)
	{
		isHit = true;
		numberOfBlocksHit++;
		if (numberOfBlocksHit >= 3)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			FVector spawnLoc = FVector(1080.0f, -440.0f, 30.0f);
			FRotator rot = FRotator::ZeroRotator;
			ATreasure* t = GetWorld()->SpawnActor<ATreasure>(treasureClass, spawnLoc, rot, spawnParams);
		}

		Destroy();
    }
	

	
}
