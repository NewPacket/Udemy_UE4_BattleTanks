// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;

// Hold barrel's properties and Elevate
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent				();

	void SetBarrelReference				(UTankBarrel * barrelToSet);
	void SetTurretReference				(UTankTurret * turretToSet);
protected:
	// Called when the game starts
	virtual void BeginPlay				() override;

public:	
	// Called every frame
	virtual void TickComponent			(float DeltaTime, ELevelTick TickType,
										FActorComponentTickFunction* ThisTickFunction) override;
			void AimAt					(FVector & hitLocation, float launchSpeed);
private:

	UTankBarrel * barrel = nullptr;
	UTankTurret * turret = nullptr;

	void MoveBarrelTowardsDirection		(FVector & aimDirection);

	void MoveTurretTowardsDirection		(FVector & aimDirection);

};
