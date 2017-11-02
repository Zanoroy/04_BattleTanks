// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right the amount this frame given the max elevation speed and Frametime
	// UE_LOG(LogTemp, Warning, TEXT("Elevate called with speed: %f"), RelativeSpeed);
	auto ElevationSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = ElevationSpeed * MaxDegressPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	// auto time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f: %f - elevation"), time, Elevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}

