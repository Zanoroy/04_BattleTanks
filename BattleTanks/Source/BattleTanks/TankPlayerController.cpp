// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controler: Begin play"));
	GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("Player Tank: Tick"));

	// Move the Turret to the crosshair
	AimTowardCrosshair();

	// Colour the crosshiar if we are aimed at the target

}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* MyTank = Cast<ATank>(GetPawn());
	return MyTank;
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	// Get the world location if linetrace through the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell controller tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	// Find the Pixels on the screen UI to get the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation, 
		ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	FVector CameraWorldDirection;

	// Deproject the position to the world position
	if (this->DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldDirection,
		LookDirection
	))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	HitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	// Line trace through the cross hair position...
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * TankRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);
	return false;
}
