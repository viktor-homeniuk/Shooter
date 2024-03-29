// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UInputComponent;
class AGun;

UCLASS(config=Game)
class AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	void ToggleAlarm(bool State = false);
	void Fire();

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Jump() override;
	void MoveForward(float Value);
	void MoveRight(float Value);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Animation Flow")
	bool bIsAiming = false;

	UPROPERTY(BlueprintReadWrite, Category = "Animation Flow")
	bool bIsCrouching = false;

	UPROPERTY(BlueprintReadWrite, Category = "Animation Flow")
	bool bIsJumping = false;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunType;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName GunSocket;

	UPROPERTY()
	AGun* Gun;

};

