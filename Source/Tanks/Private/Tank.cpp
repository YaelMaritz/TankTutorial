// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"


// Constructor
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	// true if Timer is bigger than ReloadTime
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTimeStamp) > ReloadTimeInSeconds;

	// protect pointer & check timer
	if (Barrel && isReloaded)
	{
		// Spawn projectile at socket and shoot
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Barrel Tip")), Barrel->GetSocketRotation(FName("Barrel Tip")));
		Projectile->LaunchProjectile(LaunchSpeed);

		// Reset Timer
		LastFireTimeStamp = FPlatformTime::Seconds();
	}
}
