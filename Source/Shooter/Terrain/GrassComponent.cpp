// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "GrassComponent.h"

UGrassComponent::UGrassComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UGrassComponent::BeginPlay() {
	Super::BeginPlay();
	Spawn();
}

void UGrassComponent::Spawn() {
	for (size_t i = 0; i < Count; ++i) {
		FVector Location = FMath::RandPointInBox(Extents);
		AddInstance(FTransform(Location));
	}
}
