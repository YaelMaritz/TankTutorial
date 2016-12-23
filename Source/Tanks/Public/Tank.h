// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put includes above generated!

// Forward Declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;
class UTankAimingComponent;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	/// Methods
	UFUNCTION(BlueprintCallable, Category = TankSetup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = TankSetup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	/// Properties
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	// Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	double LastFireTimeStamp = 0;

	/// Methods
	ATank();

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;
};
