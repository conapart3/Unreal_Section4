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
		GetControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY; // size of the current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation); //(calling constructor)

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection; // out parameters for the below method

	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		// Line trace along that look direction and see what we hit (up to a max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(/*Line trace like a ray-cast?*/
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility) /*Hit anything that is visible*/
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;//to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}
