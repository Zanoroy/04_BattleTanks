// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* TargetTank = GetPlayerTank();
	if (TargetTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target found: %s"), *TargetTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to locate target tank!!! What do I do now. I am a tank with no purpose"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank() || !GetControlledTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

