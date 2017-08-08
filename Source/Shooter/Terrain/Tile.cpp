// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Tile.h"


ATile::ATile() {
	PrimaryActorTick.bCanEverTick = false;
	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Ground"));
}

void ATile::PlaceActors(TSubclassOf<AActor> Prop, int32 MinNumberOfProps, int32 MaxNumberOfProps) {
	// Setup variables
	FVector Max(4000, 4000, 0);
	FBox Bounds(FVector(), Max);
	FVector SpawnPoint;
	int32 NumberOfProps = FMath::RandRange(MinNumberOfProps, MaxNumberOfProps);
	// Spawn Actors at random points within box
	for (int32 i = 0; i < NumberOfProps; ++i) {
		SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(Prop);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ATile::BeginPlay() {
	Super::BeginPlay();
}

void ATile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

