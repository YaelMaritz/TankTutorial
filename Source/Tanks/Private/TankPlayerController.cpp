// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankPlayerController.h"

// Begin Play
void ATankPlayerController::BeginPlay()
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
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimAtCrosshair();

}

// Get a reference to the controlled ATank Pawn
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); // this.GetPawn
}

// Send the ATank pawn the aim-vector of the cross-hair (if it can hit something)
void ATankPlayerController::AimAtCrosshair()
{
	FVector HitLocation; // OUT parameter

	// protect the pointer
	if (!GetControlledTank()) { return; }

	// if we are aiming at something relevant
	if (GetCrossHairHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

/* GetCrossHairHitLocation - Gets the hit location from a Line-Trace going through the cross-hair on screen
@param FVector& - OUT Vector of what the Line-Trace hit
@return bool - false if no hit. */
bool ATankPlayerController::GetCrossHairHitLocation(FVector& HitLocation) const
{
	// Find cross-hair position
	int32 ViewPortSizeX, ViewPortSizeY; // OUT Parameters
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto CrossHairPosition = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	// "De-project" the screen position of the cross-hair to a word direction
	FVector LookDirection; // OUT Parameter
	if (GetLookDirection(CrossHairPosition, LookDirection))
	{
		// Line-trace along LookDirection, see what we hit (up to max range)
		GetLineTraceHitLocation(LookDirection, HitLocation);
	}
	return true;
}

/* GetLookDirection -  Gets a 2D-vector and OUTs a 3D unit-vector
	@param FVector2D - 2D position to convert
	@param FVector& - OUT 3D position and direction (in World Space) notice: this is a unit-vector
	@return bool - false if unable to determine value. */
bool ATankPlayerController::GetLookDirection(FVector2D CrossHairPosition, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Unneeded OUT Parameter
	return DeprojectScreenPositionToWorld(CrossHairPosition.X, CrossHairPosition.Y, CameraWorldLocation, LookDirection);
}

/* GetLookVectroHitLocation - Does a 'Visibility' Line Trace according to a given Unit-Vector + 'LineTraceRange'
	@param FVector - 3D Unit-Vector of where the tank is aiming at
	@param FVector& - OUT Vector of where the Line-Trace hit (0 if Line-Trace was false)
	@return bool - false if Line-Trace was unsuccessful */
bool ATankPlayerController::GetLineTraceHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto LineTraceStart = PlayerCameraManager->GetCameraLocation();
	auto LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
