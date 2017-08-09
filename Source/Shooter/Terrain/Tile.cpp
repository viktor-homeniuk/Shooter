// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Tile.h"

ATile::ATile() {
	PrimaryActorTick.bCanEverTick = false;
	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Ground"));
}

void ATile::RandomlyPlaceStaticActors(TSubclassOf<AActor> Actor, int32 MinNumberOfProps, int32 MaxNumberOfProps, float Radius, float MinScale, float MaxScale) {
	if (!Actor) {
		UE_LOG(LogTemp, Error, TEXT("[ATile::PlaceActors]: Actor not specified"));
		return;

	}
	Place(Actor, MinNumberOfProps, MaxNumberOfProps, Radius, MinScale, MaxScale);
}

void ATile::RandomlyPlaceAIPawns(TSubclassOf<APawn> Pawn, int32 MinNumberOfPawns, int32 MaxNumberOfPawns, float Radius) {
	if (!Pawn) {
		UE_LOG(LogTemp, Error, TEXT("[ATile::PlaceAIPawns]: Pawn not specified"));
		return;
	}
	Place(Pawn, MinNumberOfPawns, MaxNumberOfPawns, Radius, 1.0f, 1.0f);
}

template<typename T>
void ATile::Place(T Actor, int32 MinNumberOfActors, int32 MaxNumberOfActors, float Radius, float MinScale, float MaxScale) {
	int32 NumberOfProps = FMath::RandRange(MinNumberOfActors, MaxNumberOfActors);

	// Spawn Actors at random points within box
	for (int32 i = 0; i < NumberOfProps; ++i) {
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		FSpawnTransform Transform = {
			FVector(0),
			FRotator(0, FMath::RandRange(-180.0f, 180.0f), 0),
			FVector(RandomScale)
		};
		if (FindEmptyLocation(Transform.Location, Radius * RandomScale)) {
			PlaceActor(Actor, Transform);
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
	static FBox Bounds(FVector(0), FVector(4000.0f, 4000.0f, 0.0f));
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

void ATile::PlaceActor(TSubclassOf<AActor> Actor, const FSpawnTransform& Transform) {
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(Actor, Transform.Location, Transform.Rotation);
	if (Spawned == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("[ATile::PlaceActor<AActor>]Failed to spawn new Actor at position: %s"), *Transform.Location.ToString());
		return;
	}
	Spawned->SetActorScale3D(Transform.Scale);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATile::PlaceActor(TSubclassOf<APawn> Pawn, const FSpawnTransform& Transform) {
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(Pawn, Transform.Location, Transform.Rotation);
	if (Spawned == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("[ATile::PlaceActor<AActor>]Failed to spawn new Pawn at position: %s"), *Transform.Location.ToString());
		return;
	}
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SpawnDefaultController();
}

