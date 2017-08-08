// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Gun.h"
#include "ShooterProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"


// Sets default values
AGun::AGun() {
	PrimaryActorTick.bCanEverTick = false;

	// Create a Gun mesh
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	SetRootComponent(GunMesh);

	// Create a Muzzle object
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform);

}

void AGun::Fire() {
	// Spawn Projectile
	if (Projectile != nullptr && Muzzle != nullptr) {
		const FRotator Rotation = Muzzle->GetComponentRotation();
		const FVector Location = Muzzle->GetComponentLocation();
		GetWorld()->SpawnActor<AShooterProjectile>(Projectile, Location, Rotation);
	}
	// Report noise event by Gun owner
	MakeNoise(1.0f, Cast<APawn>(GetParentActor()));

	// Play sound
	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}
