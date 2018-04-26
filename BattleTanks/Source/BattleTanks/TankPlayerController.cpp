// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Vector.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#define OUT
#define IN


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto aimingComponent = GetControlledTankAimingComponent();
	FoundAimingComponent(aimingComponent);
}

ATank* ATankPlayerController::GetControlledTank() const
{
	if (!ensure(GetPawn()))
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn"))
	}
	return Cast<ATank>(GetPawn());
}

UTankAimingComponent* ATankPlayerController::GetControlledTankAimingComponent() const
{
	if (!ensure(GetControlledTank()))
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn"))
		return nullptr;
	}
	auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	return aimingComponent;
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrossHair();
};

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector hitLocation;
	if (GetSightRayHitLocation(IN hitLocation))
	{
		GetControlledTankAimingComponent()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT hitLocation) const
{
	//FindCrosshair possition
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	if (!viewportSizeX) { return false; }
	const FVector2D crossHair2DPosition{viewportSizeX * crossHairX, viewportSizeY * crossHairY};
	FVector lookDirection;
	if (GetLookDirection(crossHair2DPosition, lookDirection))
	{
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& crossHair2DPosition, FVector& lookDirection) const
{
	FVector worldLocation;
	return DeprojectScreenPositionToWorld(crossHair2DPosition.X, crossHair2DPosition.Y, worldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& lookDirection, FVector& hitLocation) const
{
	FHitResult hitResult;
	const auto startLocation = PlayerCameraManager->GetCameraLocation();
	const auto endPosition = startLocation + (lookDirection * lineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endPosition,
		ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(-1, -1, -1);
	return false;
}