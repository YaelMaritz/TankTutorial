// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Adjust the amount of degrees that are elevated per seconds to a relative scale (-1 max town angle, 1 ,max up angle) and bind to FPS (Delta)
	auto ElevationSegment = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;

	// Add the new elevation amount to the current rotation
	auto UnclampedElevation = RelativeRotation.Pitch + ElevationSegment;
	auto NewElevation = FMath::Clamp<float>(UnclampedElevation, MinElevationDegrees, MaxElevationDegrees);

	// Move the barrel the correct Elevation
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}