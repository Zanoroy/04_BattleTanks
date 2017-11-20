// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward declaration
class UTankTurret;
class UTankTrack;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetLeftTrackReference(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetRightTrackReference(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void FireProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeinSeconds = 3.0f;

	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileVelocity = 4000.0f;

	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	double LastTimeFired = 0;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UMovementComponent* TankMovementComponent = nullptr;

};
