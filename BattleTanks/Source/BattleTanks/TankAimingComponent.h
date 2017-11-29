// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Reloading,
	Locked
};


// Forward declaration
class UTankBarrel; 
class UTankTurret;

// Hold's properties for the Tank Barrel.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float ProjectileVelocity);

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Initalise(UTankBarrel * Barrel, UTankTurret * Turret);
	
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	void MoveBarrelTowards(FVector*);
	void MoveTurretTowards(FVector*);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

};