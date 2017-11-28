// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHOOTER_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
	AMyGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void StartPlay() override;
	
};
