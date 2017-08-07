// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ShooterCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AShooterCharacter::AShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(45.0f, 100.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	USkeletalMeshComponent* Mesh = GetMesh();
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));

	// Create a gun mesh component
	//GunActor = GetWorld()->SpawnActor<AGun>(GunClass);
	//GunActor->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//GunActor->bCastDynamicShadow = false;
	//GunActor->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//GunActor->SetupAttachment(RootComponent);

	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(FP_Gun);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	//// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

void AShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	if (GunType == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s: Gun Type not specified"), *GetName());
	}
	// Setup Gun Actor and bind it to fire action
	GunActor = GetWorld()->SpawnActor<AGun>(GunType);
	GunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GunSocket);
	GunActor->SetAnimationInstance(GetMesh()->GetAnimInstance());
	if (InputComponent != nullptr) {
		InputComponent->BindAction("Fire", IE_Pressed, GunActor, &AGun::Fire);
	}
}

void AShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up Gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AShooterCharacter::Jump() {
	Super::Jump();
	UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->JumpZVelocity = 400.0f;
}

//void AShooterCharacter::OnFire()
//{
//	// try and fire a projectile
//	if (ProjectileClass != NULL)
//	{
//		UWorld* const World = GetWorld();
//		if (World != NULL)
//		{
//			if (bUsingMotionControllers)
//			{
//				//const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
//				//const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
//				//World->SpawnActor<AShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
//			}
//			else
//			{
//				const FRotator SpawnRotation = GetControlRotation();
//				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
//				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
//
//				//Set Spawn Collision Handling Override
//				FActorSpawnParameters ActorSpawnParams;
//				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//				// spawn the projectile at the muzzle
//				World->SpawnActor<AShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//			}
//		}
//	}
//
//	// try and play the sound if specified
//	if (FireSound != NULL)
//	{
//		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
//	}
//
//	// try and play a firing animation if specified
//	if (FireAnimation != NULL)
//	{
//		// Get the animation object for the arms mesh
//		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
//		if (AnimInstance != NULL)
//		{
//			AnimInstance->Montage_Play(FireAnimation, 1.f);
//		}
//	}
//}

//void AShooterCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if (TouchItem.bIsPressed == true)
//	{
//		return;
//	}
//	TouchItem.bIsPressed = true;
//	TouchItem.FingerIndex = FingerIndex;
//	TouchItem.Location = Location;
//	TouchItem.bMoved = false;
//}
//
//void AShooterCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if (TouchItem.bIsPressed == false)
//	{
//		return;
//	}
//	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
//	{
//		//OnFire();
//	}
//	TouchItem.bIsPressed = false;
//}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AShooterCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

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

//bool AShooterCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
//{
//	bool bResult = false;
//	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
//	{
//		bResult = true;
//		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AShooterCharacter::BeginTouch);
//		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AShooterCharacter::EndTouch);
//
//		//Commenting this out to be more consistent with FPS BP template.
//		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AShooterCharacter::TouchUpdate);
//	}
//	return bResult;
//}
