// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"


// Constructor
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector LaunchHitLocation, float LaunchSpeed)
{
	// protect the pointers
	if (!Barrel) { UE_LOG(LogTemp, Error, TEXT("NO Barrel")); return; }
	if (!Turret) { UE_LOG(LogTemp, Error, TEXT("NO Turret")); return; }

	FVector LaunchVelocity; // OUT Parameter
	FVector LaunchStartLocation = Barrel->GetSocketLocation(FName("Barrel Tip"));

	// if there is a possible trajectory to hit the target, get its velocity vector
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, LaunchStartLocation, LaunchHitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal(); // Get a Unit-vector from a vector (0,0,0 if shorter than unit)
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// The difference between the Barrel Rotation and where it needs to be to hit.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator; // Delta = Difference
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Turn(DeltaRotator.Yaw);
}
