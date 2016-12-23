// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/Tank.h"
#include "Public/TankAIController.h"

// Begin Play
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto tank = Cast<ATank>(GetPawn());
	if (!tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController Does not possess a tank"));
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController is possessing: %s"), *tank->GetName());
	}
}

// Tick
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); // TODO: Find out why player pawn is not index 0
	auto ThisTank = Cast<ATank>(GetPawn());

	/// protect the pointer
	if (PlayerPawn)
	{ 
		auto PlayerTank = Cast<ATank>(PlayerPawn);

		// TODO: Move towards the player

		/// Aim at player
		// UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *ThisTank->GetName(), *PlayerTank->GetName());
		ThisTank->AimAt(PlayerTank->GetActorLocation());

		/// Fire if ready
		ThisTank->Fire();
	}
}