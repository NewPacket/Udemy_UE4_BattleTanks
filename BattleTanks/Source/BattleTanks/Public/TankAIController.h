// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	ATank * GetControlledTank() const;
	virtual void BeginPlay() override;

	UTankAimingComponent* GetControlledTankAimingComponent() const;

	ATank* GetPlayerTank() const;
	
	virtual void Tick(float DeltaSeconds) override;

	float acceptanceRadius = 30;
};
