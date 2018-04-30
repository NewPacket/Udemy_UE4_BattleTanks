// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto slippageSpeed = FVector::DotProduct(FVector::RightVector, GetForwardVector());

	auto correctionAcceleration = -slippageSpeed / DeltaTime * FVector::RightVector;
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto correctForce = tankRoot->GetMass() * correctionAcceleration;
	//UE_LOG(LogActor, Warning, TEXT("Appling Force %s"), *correctForce.ToString())
	tankRoot->AddForceAtLocation(correctForce, GetComponentLocation());
}


void UTankTrack::SetThrottle(float throttle)
{

	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	UE_LOG(LogActor, Warning, TEXT("Throttle Force %s"), *forceApplied.ToString())
}


