// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAIController.h"

// Begin Play
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController Does not possess a tank"));
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController is possessing: %s"), *tank->GetName());
	}
}

// Tick
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	// protect the pointer
	if (GetControlledTank() && GetPlayerTank())
	{ 
		// TODO: Move towards the player

		// Aim at player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }

	return Cast<ATank>(PlayerTank);
}