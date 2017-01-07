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


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair(DeltaTime);
}


// We will be getting which tank is being controlled for the Tank controller
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair(float DeltaTime)
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out param

	if (GetSightRayHitLocation(HitLocation))// has a side effect, it is going to line trace
	{
		//if it hits the landscape
		// Tell controlled tank to aim at this point
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Cast out a ray cast
	HitLocation = FVector(3.0, 2.0, 1.0);
	return true;
}
