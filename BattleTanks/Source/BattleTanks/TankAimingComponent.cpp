// Copyright Bruce Quinton (ish)

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initalise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileVelocity)
{
	if (!Barrel) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());  return; }
	if (!Turret) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate turret"), *GetOwner()->GetName());  return; }

	FVector outTossVelocity;
	FVector Startpoint = Barrel->GetSocketLocation(FName("ProjectileLaunchPoint"));

	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
		outTossVelocity,
		Startpoint,
		HitLocation,
		ProjectileVelocity,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);
		
	if(bHasAimSolution)
	{
		FVector desiredAimAt = outTossVelocity.GetSafeNormal();
		MoveBarrelTowards(&desiredAimAt);
		MoveTurretTowards(&desiredAimAt);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector* AimDirection)
{
	if (!Barrel) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());  return; }
	// Calculate the movement required
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector* AimDirection)
{
	if (!Turret) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate turret"), *GetOwner()->GetName());  return; }
	// Calculate the movement required
	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;

	Turret->Rotate(deltaRotator.Yaw);
}
