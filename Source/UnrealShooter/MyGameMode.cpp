// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "Engine.h"

AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn>FoundPawn(TEXT("Pawn'/Game/Blueprints/BP_FPSCharacter.BP_FPSCharacter_C'"));

	if (FoundPawn.Class != NULL)
	{
		DefaultPawnClass = FoundPawn.Class;
	}
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}