// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float throttle);

	UFUNCTION(BlueprintCallable)
	void IntendTurn(float throttle);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:

	UTankTrack * leftTrack = nullptr;
	UTankTrack * rightTrack = nullptr;
};
