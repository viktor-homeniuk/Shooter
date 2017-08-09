// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class SHOOTER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> Actor, int32 MinNumberOfProps = 1, int32 MaxNumberOfProps = 1, float Radius = 500.0f, float MinScale = 1.0f, float MaxScale = 1.0f);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& Location, float Radius);
	void PlaceActor(TSubclassOf<AActor> Actor, FVector Location, FRotator Rotation, float Scale);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* GroundMesh;

};
