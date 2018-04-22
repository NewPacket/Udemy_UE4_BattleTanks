// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
	tankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Tank Movement component"));

}

void ATank::SetBarrelReference(UTankBarrel * barrelToSet)
{
	tankAimingComponent->SetBarrelReference(barrelToSet);
	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
	tankAimingComponent->SetTurretReference(turretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector& hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	if (!barrel) { return; }
	bool isReloaded = FPlatformTime::Seconds() - lastFireTime > fireRate;

	if (isReloaded)
	{
		lastFireTime = FPlatformTime::Seconds();
		FActorSpawnParameters spawnParams;
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile")),
			spawnParams);
		if (projectile)
			projectile->LaunchProjectile(launchSpeed);
	}
}
