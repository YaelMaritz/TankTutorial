// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UTankAimingComponent();

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// TODO: void SetTurretReference(UStaticMeshComponent* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrel(FVector AimDirection);
};
