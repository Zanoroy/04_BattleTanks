// Fill out your copyright notice in the Description page of Project Settings.
/// #include "Components/ActorComponent.h"
/// #include "GameFramework/Actor.h"


#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	ATank* GetControlledTank() const;
	
private:
	void AimTowardCrosshair();

	// Start the tank barrel moving toward the where the crosshair is in the world..
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float TankRange = 1000000.0f;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

};
