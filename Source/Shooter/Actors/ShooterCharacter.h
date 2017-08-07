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
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Jump() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

};

