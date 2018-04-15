// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Hold barrel's properties and Elevate
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = ("Collision"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float degreesPerSecond);
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxDegreesPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float minElevationDegrees = 0;
};
