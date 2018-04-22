// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	UE_LOG(LogActor, Warning, TEXT("Appling Force %s"),*forceApplied.ToString())
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


