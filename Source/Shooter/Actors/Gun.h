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

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class USceneComponent* Muzzle;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<class AShooterProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class USoundBase* FireSound;

};
