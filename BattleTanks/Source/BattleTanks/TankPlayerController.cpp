// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Vector.h"
#include "Engine/World.h"

#define OUT
#define IN

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const auto pawn = GetControlledTank();
	if (pawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller tank name %s"), *(pawn->GetName()))
	}
	else
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possed"))
	}
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	if (GetPawn() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn"))
	}
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrossHair();
};

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector hitLocation;
	if (GetSightRayHitLocation(IN hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
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
		return GetLookVectorHitLocation(lookDirection, hitLocation);
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