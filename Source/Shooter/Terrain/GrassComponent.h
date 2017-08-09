// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "TerrainGeneration", meta = (BlueprintSpawnableComponent))
class SHOOTER_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UGrassComponent();
	void BeginPlay() override;
	void Spawn();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FBox Extents;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 Count;

};
