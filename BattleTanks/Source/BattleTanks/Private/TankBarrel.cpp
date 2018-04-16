// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float degreesPerSecond)
{

	degreesPerSecond = FMath::Clamp<float>(degreesPerSecond, -1, +1);
	auto elevationChange = degreesPerSecond * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp<float>(newElevation, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}


