// Copyright Bruce Quinton (ish)

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right the amount this frame given the max elevation speed and Frametime
	auto ElevationSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = ElevationSpeed * MaxDegressPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}

