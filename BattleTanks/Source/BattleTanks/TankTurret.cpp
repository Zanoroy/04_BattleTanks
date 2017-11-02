// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::RotateToTarget(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Elevate called with speed: %f"), RelativeSpeed);
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegressPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	// auto time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f: %f - elevation"), time, Elevation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

