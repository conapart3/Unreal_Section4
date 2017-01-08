// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank* GetControlledTank() const; // we won't change any member variables of the ATank class therefore const.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Start the tank moving the barrel so that the shot would hit where the crosshair intersects the world.
	void AimTowardsCrosshair(float DeltaTime);

	// Return an OUT parameter, true if hit landscape. Takes a reference.
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;//distance across screen

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;//distance down screen

	// Get the Vector in the world hit by the player's line trace pointing at the crosshair
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	// Get the vector of the direction where the crosshair is looking aiming in the world
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;//10km

};
