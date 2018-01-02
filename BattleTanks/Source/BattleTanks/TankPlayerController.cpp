// Copyright Bruce Quinton (ish)

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { 
		
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Error, TEXT("%f: - Tank aiming component not found!"), time);
		return; 
	}
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Move the Turret to the crosshair
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* MyTank = Cast<ATank>(GetPawn());
	return MyTank;
}

void ATankPlayerController::AimTowardCrosshair()
{
	// Check we have access to the controlled tank.
	if (!GetPawn() || !GetControlledTank()) { return; }

	FVector HitLocation;

	// Get the world location if linetrace through the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell controller tank to aim at this point
		auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { 
			auto time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Error, TEXT("%f: - Tank aiming component STILL not found!"), time);
			return; 
		}
		AimingComponent->AimAt(HitLocation);
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
