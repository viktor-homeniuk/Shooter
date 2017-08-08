// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AShooterCharacter::AShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(45.0f, 100.0f);
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
}

void AShooterCharacter::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();
	if (GunType == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s: Gun Type not specified"), *GetName());
	}
	// Setup Gun Actor and bind it to fire action
	Gun = GetWorld()->SpawnActor<AGun>(GunType);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GunSocket);
	Gun->SetAnimationInstance(GetMesh()->GetAnimInstance());
	if (InputComponent) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::Fire);
	}
}

void AShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up Gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AShooterCharacter::Fire() {
	Gun->Fire();
}

void AShooterCharacter::Jump() {
	Super::Jump();
	UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->JumpZVelocity = 400.0f;
}

void AShooterCharacter::MoveForward(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AShooterCharacter::MoveRight(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShooterCharacter::ToggleAlarm(bool State) {
	bIsAiming = State;
}
