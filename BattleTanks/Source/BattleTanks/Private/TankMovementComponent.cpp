// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float throttle)
{
	//Send throttle to l and r tracks of tank
	leftTrack->SetThrottle(throttle);
	rightTrack->SetThrottle(throttle);
}

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) { return; }
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}



