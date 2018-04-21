// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	turret = turretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector& hitLocation, float launchSpeed)
{
	if (!barrel || !turret) { return;}

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
		UE_LOG(LogTemp, Warning, TEXT("%s need to aim at %s"),*GetOwner()->GetName(), *aimDirection.ToString())
	}
}

void UTankAimingComponent::MoveBarrelTowardsDirection(FVector& aimDirection)
{
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotation = aimDirection.Rotation();
	auto deltaRotator  = aimAsRotation - barrelRotator;
	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate(deltaRotator.Yaw);
}

