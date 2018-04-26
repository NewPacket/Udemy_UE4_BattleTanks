// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include <Engine/World.h>
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

UTankAimingComponent* ATankAIController::GetControlledTankAimingComponent() const
{
	auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	return aimingComponent;
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	const auto playerTank = GetPlayerTank();
	if (!ensure(playerTank)) { return; }
	MoveToActor(playerTank, acceptanceRadius);
	auto actorLocation = playerTank->GetActorLocation();
	GetControlledTankAimingComponent()->AimAt(actorLocation);
	GetControlledTankAimingComponent()->Fire();
}



