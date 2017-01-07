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

};
