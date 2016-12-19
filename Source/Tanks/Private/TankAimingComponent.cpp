// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/TankBarrel.h"
#include "Public/TankAimingComponent.h"


// Constructor
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector LaunchHitLocation, float LaunchSpeed)
{
	// protect the pointer
	if (!Barrel) { 
		UE_LOG(LogTemp, Error, TEXT("NO Barrel"));
		return; 
	}

	FVector LaunchVelocity; // OUT Parameter
	FVector LaunchStartLocation = Barrel->GetSocketLocation(FName("Barrel Tip"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, LaunchStartLocation, LaunchHitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal(); // Get a Unit-vector from a vector
		MoveBarrel(AimDirection);
		auto TimeStamp = GetWorld()->GetTimeSeconds();
		auto OwnerName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%f | %s: Aiming vector found"), TimeStamp, *OwnerName);
	}
	else
	{
		auto TimeStamp = GetWorld()->GetTimeSeconds();
		auto OwnerName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%f | %s: Aiming vector NOT found"), TimeStamp, *OwnerName);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// The difference between the Barrel Rotation and where it needs to be to hit.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator; // Delta = Difference
	
	Barrel->Elevate(5); // TODO: Remove TEST number
}