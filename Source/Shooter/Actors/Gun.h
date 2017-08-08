// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UAnimInstance;

UCLASS()
class SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	void Fire();
	FORCEINLINE void SetAnimationInstance(UAnimInstance* Instance) { AnimInstance = Instance; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<class AShooterProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", DisplayName = "Fire Animation")
	class UAnimMontage* AnimMontage;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class USceneComponent* Muzzle;

	UPROPERTY()
	UAnimInstance* AnimInstance;
};
