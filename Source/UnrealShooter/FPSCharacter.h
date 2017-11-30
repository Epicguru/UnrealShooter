// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// First Person Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FPCameraComponent;

	// First Person Mesh (arms)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FirstPersonMesh;

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	// Constructor for AFPSCharacter
	AFPSCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	UFUNCTION()
	void HandleForwardMovement(float Value);
	UFUNCTION()
	void HandleHorizontalMovement(float Value);

	UFUNCTION()
	void OnJumpDown();

	UFUNCTION()
	void OnJumpUp();

};
