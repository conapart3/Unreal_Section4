// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("PlayerController not posessing a tank."));
	}

	UE_LOG(LogTemp, 
		Warning, 
		TEXT("PlayerController begin play... Controlled tank is %s"), 
		*(ControlledTank->GetName()));
}

// We will be getting which tank is being controlled for the Tank controller
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
