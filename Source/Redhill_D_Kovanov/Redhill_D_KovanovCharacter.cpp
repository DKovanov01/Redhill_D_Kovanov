// Copyright Epic Games, Inc. All Rights Reserved.

#include "Redhill_D_KovanovCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Redhill_D_Kovanov.h"
#include "SideCamera.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ARedhill_D_KovanovCharacter::ARedhill_D_KovanovCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	// The side camera actor for side view;
	AActor* Camera = UGameplayStatics::GetActorOfClass(this, ASideCamera::StaticClass());
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (SideCamera)	{
			PC->SetViewTarget(SideCamera);
		}
	}	
}

void ARedhill_D_KovanovCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARedhill_D_KovanovCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ARedhill_D_KovanovCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARedhill_D_KovanovCharacter::Look); 
		
		// Interact Key
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARedhill_D_KovanovCharacter::Interact);
		
		// Reset Key
		EnhancedInputComponent->BindAction(ResetAction, ETriggerEvent::Started, this, &ARedhill_D_KovanovCharacter::Reset);
	}
	else
	{
		UE_LOG(LogRedhill_D_Kovanov, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARedhill_D_KovanovCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ARedhill_D_KovanovCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ARedhill_D_KovanovCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ARedhill_D_KovanovCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ARedhill_D_KovanovCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ARedhill_D_KovanovCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

// Interaction Function - Debug;
void ARedhill_D_KovanovCharacter::Interact()
{
UE_LOG(LogTemp, Warning, TEXT("E key pressed!"));
}

// Reset function - resets the level;
void ARedhill_D_KovanovCharacter::Reset()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
	
}