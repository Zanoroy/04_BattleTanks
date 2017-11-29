// Copyright Bruce Quinton (ish)

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);


	// TODO: clamp throttle value
	auto ForceApplied = GetForwardVector() * Throttle * MaximumDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);

}

