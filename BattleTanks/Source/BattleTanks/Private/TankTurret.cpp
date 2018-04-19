// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float degreesPerSecond)
{
	degreesPerSecond = FMath::Clamp<float>(degreesPerSecond, -1, +1);
	auto rotationChange = degreesPerSecond * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + rotationChange;
	auto rotation = FMath::Clamp<float>(newRotation, -maxRotationDegreesAbsolute, maxRotationDegreesAbsolute);

	SetRelativeRotation(FRotator(0, rotation, 0));
}


