// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"

// Forward decelerations
class ATank;

UCLASS()
class TANKS_API ATankAIController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;
};
