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

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Jump() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunType;
	AGun* GunActor;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName GunSocket;

	//struct TouchData
	//{
	//	TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
	//	bool bIsPressed;
	//	ETouchIndex::Type FingerIndex;
	//	FVector Location;
	//	bool bMoved;
	//};
	//void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	//TouchData	TouchItem;
	
protected:
	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

};

