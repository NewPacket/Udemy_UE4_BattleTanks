// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	if (!ensure(barrelToSet && turretToSet)) { return; }
	barrel = barrelToSet;
	turret = turretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool isReloaded = FPlatformTime::Seconds() - lastFireTime > fireRate;

	if (!isReloaded)
	{
		aimingState = EAimingState::RELOADING;
	}
	else if (isRotating)//
		aimingState = EAimingState::AIMING;
	else
	{
		aimingState = EAimingState::LOCKED;
	}

}

void UTankAimingComponent::AimAt(FVector& hitLocation)
{
	if (!ensure(barrel && turret))
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel or turret"))
		return;
	}

	FVector launchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Barrel"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowardsDirection(aimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s need to aim at %s"), *GetOwner()->GetName(), *aimDirection.ToString())
	}
}

void UTankAimingComponent::MoveBarrelTowardsDirection(FVector& aimDirection)
{
	if (!ensure(barrel && turret)) { return;}

	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotation = aimDirection.Rotation();
	auto deltaRotator  = aimAsRotation - barrelRotator;
	if (deltaRotator.Equals(FRotator::ZeroRotator, 0.1f))
	{isRotating = false;}	else	{isRotating = true;}
	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate(deltaRotator.Yaw);
	UE_LOG(LogTemp, Warning, TEXT("Rotating"))
}

void UTankAimingComponent::Fire()
{
	if (!ensure(barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel"))
		return;
	}

	bool isReloaded = FPlatformTime::Seconds() - lastFireTime > fireRate;

	if (isReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing"))
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