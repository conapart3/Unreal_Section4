// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not posessing a tank."));
	}
	// Log the AI controlled tank name
	UE_LOG(LogTemp, Warning, TEXT("AIController begin play... Controlled tank is %s"), *(ControlledTank->GetName()));

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not targetting a player tank."));
	}
	// Log the targetted player controlled tank
	UE_LOG(LogTemp,
		Warning, TEXT("AIController aiming at player tank: %s"), *(PlayerTank->GetName()));
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())/*we already have a method for getting the player tank!!!*/
	{
		// todo Move towards the player

		// Aim towards the player
		GetControlledTank()
			->AimAt(GetPlayerTank()->GetActorLocation());

		// fire if ready
	}
}
