// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) { return; }
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throttle)
{
	//Send throttle to l and r tracks of tank
	leftTrack->SetThrottle(throttle);
	rightTrack->SetThrottle(throttle);
}

void UTankMovementComponent::IntendTurn(float throttle)
{
	//Send throttle to l and r tracks of tank
	leftTrack->SetThrottle(-throttle);
	rightTrack->SetThrottle(throttle);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto AIIntededDirection = MoveVelocity.GetSafeNormal();
	auto tankForward = GetOwner()->GetActorForwardVector();
	auto forwardThrow = FVector::DotProduct(AIIntededDirection, tankForward);
	auto angleThrow = FVector::CrossProduct(tankForward, AIIntededDirection);

	IntendTurn(-angleThrow.Z);
	IntendMoveForward(forwardThrow);
}



