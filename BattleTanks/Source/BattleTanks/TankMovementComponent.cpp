// Copyright Bruce Quinton (ish)
#include "TankMovementComponent.h"
#include "TankTrack.h"

// Sets default values for this component's properties
UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

UFUNCTION(BlueprintCallable, Category = Movement)
void UTankMovementComponent::IntendMovementFoward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	Throw = FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	Throw = FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

// Called by AI tanks
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardSpeed = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMovementFoward(ForwardSpeed);

	auto TurnClockwise = FVector::CrossProduct(TankForwardDirection, AIForwardIntention);
	IntendTurnClockwise(TurnClockwise.Z);

}



