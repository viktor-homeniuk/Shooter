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
	//GunMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

	// Play sound
	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// Play Animation
	if (AnimInstance != nullptr && AnimMontage != nullptr) {
		AnimInstance->Montage_Play(AnimMontage, 1.0f);
	}
}
