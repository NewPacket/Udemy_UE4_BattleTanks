// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:

	void Elevate(float degreesPerSecond);

private:
	
	UStaticMeshComponent * barrel = nullptr;
	
};
