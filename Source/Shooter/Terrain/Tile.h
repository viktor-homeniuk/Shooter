// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnTransform {
	GENERATED_USTRUCT_BODY()

	FVector Location;
	FRotator Rotation;
	FVector Scale;
};


UCLASS()
class SHOOTER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void RandomlyPlaceStaticActors(TSubclassOf<AActor> Actor, int32 MinNumberOfProps = 1, int32 MaxNumberOfProps = 1, float Radius = 500.0f, float MinScale = 1.0f, float MaxScale = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void RandomlyPlaceAIPawns(TSubclassOf<APawn> Pawn, int32 MinNumberOfPawns = 1, int32 MaxNumberOfPawns = 1, float Radius = 200.0f);

private:
	template<typename T>
	void Place(T Actor, int32 MinNumberOfActors, int32 MaxNumberOfActors, float Radius, float MinScale, float MaxScale);
	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& Location, float Radius);
	void PlaceActor(TSubclassOf<AActor> Actor, const FSpawnTransform& Transform);
	void PlaceActor(TSubclassOf<APawn> Pawn, const FSpawnTransform& Transform);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* GroundMesh;

};
