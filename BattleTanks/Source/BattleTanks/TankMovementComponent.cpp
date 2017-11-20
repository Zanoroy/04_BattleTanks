// Fill out your copyright notice in the Description page of Project Settings.
#include "TankTrack.h"
#include "TankMovementComponent.h"

// Sets default values for this component's properties
UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}
UFUNCTION(BlueprintCallable, Category = Movement)
void UTankMovementComponent::IntendMovementFoward(float Throw)
{

}

