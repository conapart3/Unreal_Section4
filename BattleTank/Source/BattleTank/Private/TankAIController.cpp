// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("AIController not posessing a tank."));
	}

	UE_LOG(LogTemp,
		Warning,
		TEXT("AIController begin play... Controlled tank is %s"),
		*(ControlledTank->GetName()));
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
