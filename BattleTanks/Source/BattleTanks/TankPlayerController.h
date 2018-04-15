// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(const FVector2D & crossHair2DPosition, FVector & lookDirection) const;
	bool GetLookVectorHitLocation(FVector & lookDirection, FVector & hitLocation) const;


private:
	UPROPERTY(EditAnywhere)
	float crossHairX =  0.5f;

	UPROPERTY(EditAnywhere)
	float crossHairY = 0.3333f;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 10000.f;
};
