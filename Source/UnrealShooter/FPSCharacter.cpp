// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Constructor.
AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create a CameraComponent 
	FPCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FPCameraComponent->AttachTo(GetCapsuleComponent());

	// Position the camera a bit above the eyes
	FPCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	// Allow the pawn to control rotation.
	FPCameraComponent->bUsePawnControlRotation = true;

	// everyone but the owner can see the regular body mesh
	GetMesh()->SetOwnerNoSee(true);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachTo(FPCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
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

	// Movement.
	InputComponent->BindAxis("Forward Movement", this, &AFPSCharacter::HandleForwardMovement);
	InputComponent->BindAxis("Horizontal Movement", this, &AFPSCharacter::HandleHorizontalMovement);

	// Mouse look.
	InputComponent->BindAxis("Horizontal Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("Vertical Turn", this, &AFPSCharacter::AddControllerPitchInput);

	// Jumping.
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnJumpDown);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnJumpUp);
}

void AFPSCharacter::HandleForwardMovement(float Value)
{
	// Handles moving in the direction of the camera.

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Magenta, TEXT("Forward movement is: %s"));

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
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::OnJumpDown()
{
	// Called when jump button pressed.

	bPressedJump = true;
}

void AFPSCharacter::OnJumpUp() 
{
	// Called when jump button released.

	bPressedJump = false;
}