// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Tile.h"

ATile::ATile() {
	PrimaryActorTick.bCanEverTick = false;
	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Ground"));
}

void ATile::PlaceActors(TSubclassOf<AActor> Actor, int32 MinNumberOfProps, int32 MaxNumberOfProps, float Radius, float MinScale, float MaxScale) {
	if (!Actor) {
		UE_LOG(LogTemp, Error, TEXT("[ATile::PlaceActors]: Actor not specified"));
		return;
	}

	FVector SpawnPoint;
	int32 NumberOfProps = FMath::RandRange(MinNumberOfProps, MaxNumberOfProps);

	// Spawn Actors at random points within box
	for (int32 i = 0; i < NumberOfProps; ++i) {
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		FRotator RandomRotation = FRotator(0, FMath::RandRange(-180.0f, 180.0f), 0);
		if (FindEmptyLocation(SpawnPoint, Radius * RandomScale)) {
			PlaceActor(Actor, SpawnPoint, RandomRotation, RandomScale);
		}
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult Hit;
	FVector GlobalLocation = AActor::ActorToWorld().TransformPosition(Location);
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		Hit,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	return !bHasHit;
}

bool ATile::FindEmptyLocation(FVector& Location, float Radius) {
	static FVector Max(4000, 4000, 0);
	static FBox Bounds(FVector(), Max);
	static int32 MaxAttempts = 100;

	// Try to find empty location to spawn actor
	FVector Point;
	for (size_t i = 0; i < MaxAttempts; ++i) {
		Point = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(Point, Radius)) {
			Location = Point;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> Actor, FVector Location, FRotator Rotation, float Scale) {
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(Actor);
	Spawned->SetActorRelativeLocation(Location);
	Spawned->SetActorRotation(Rotation);
	Spawned->SetActorScale3D(FVector(Scale));
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}


void ATile::BeginPlay() {
	Super::BeginPlay();
}

void ATile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

