// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UTankMovementComponent();
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMovementFoward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnClockwise(float Throw);
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Called from the path finding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
