// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("FPS Character is being created propperly!"));
	}
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Bind input to functions.
	InputComponent->BindAxis("Forward Movement", this, &AFPSCharacter::HandleForwardMovement);
	InputComponent->BindAxis("Horizontal Movement", this, &AFPSCharacter::HandleHorizontalMovement);
}

void AFPSCharacter::HandleForwardMovement(float Value)
{
	// Handles moving in the direction of the camera.

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Magenta, TEXT("Forward movement is: %s", Value));

	if (Controller != NULL && Value != 0.f)
	{
		// Get the forward direction.
		FRotator Rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			// To my understanding, make camera look horizontal when moving? Or character controller? Kinda lost.
			Rotation.Pitch = 0.0f;
		}

		// NOTE TO SELF:
		// In unreal engine, Z is height, Y is Sideways (you know what I mean), and X is depth.

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		this->AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::HandleHorizontalMovement(float Value)
{
	// Handles moving in the direction of the camera.

	if (Controller != NULL && Value != 0.f)
	{
		// Get the forward direction.
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		this->AddMovementInput(Direction, Value);
	}
}