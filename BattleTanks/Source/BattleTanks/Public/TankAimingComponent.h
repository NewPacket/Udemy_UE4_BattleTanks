// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//
UENUM()
enum class EAimingState : uint8
{
	RELOADING = 0,
	AIMING,
	LOCKED
};

//Forward declarations for Aiming component

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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

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

	UPROPERTY(BlueprintReadOnly)
	EAimingState aimingState = EAimingState::RELOADING;

	UTankBarrel * GetBarrel() const { return barrel; };

private:
	UTankBarrel * barrel = nullptr;
	UTankTurret * turret = nullptr;

	void MoveBarrelTowardsDirection		(FVector & aimDirection);
};
