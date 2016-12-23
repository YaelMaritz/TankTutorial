// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Adjust the amount of degrees that are elevated per seconds to a relative scale (-1 max town angle, 1 ,max up angle) and bind to FPS (Delta)
	auto TurnSegment = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;

	// Add the new elevation amount to the current rotation
	auto NewTurn = RelativeRotation.Yaw + TurnSegment;

	// Move the barrel the correct Elevation
	SetRelativeRotation(FRotator(0, NewTurn, 0));
}