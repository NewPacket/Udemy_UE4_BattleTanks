// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include <Engine/World.h>


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto pawn = GetPlayerTank();
	if (pawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller posses tank name %s"), *(pawn->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possed"))
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	if (GetPawn() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn"))
	}
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
	auto actorLocation = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(actorLocation);
}



