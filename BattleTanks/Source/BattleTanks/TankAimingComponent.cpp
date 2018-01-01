// Copyright Bruce Quinton (ish)

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

// Called when the game starts or when spawned
void UTankAimingComponent::BeginPlay()
{
	// Super::BeginPlay();
	LastTimeFired = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initalise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

	if (!ensure(BarrelToSet)) { UE_LOG(LogTemp, Warning, TEXT("%s barrel was not past to the aiming component Initalise"), *GetOwner()->GetName());  return; }
	if (!ensure(TurretToSet)) { UE_LOG(LogTemp, Warning, TEXT("%s turret was not past to the aiming component Initalise"), *GetOwner()->GetName());  return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	// Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((GetWorld()->GetTimeSeconds() - LastTimeFired) < ReloadTimeinSeconds)
		FiringStatus = EFiringStatus::Reloading;
	else if (IsBarrelMoving())
		FiringStatus = EFiringStatus::Aiming;
	else
		FiringStatus = EFiringStatus::Locked;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());  return false; }
	auto barrelDirection = Barrel->GetForwardVector();

	if (barrelDirection.Equals(vDesiredAimAt, 0.01))
		return false;
	else
		return true;

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());  return; }
	if (!ensure(Turret)) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate turret"), *GetOwner()->GetName());  return; }

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
	
	if (bHasAimSolution)
	{

		vDesiredAimAt = outTossVelocity.GetSafeNormal();
		MoveBarrelTowards(&vDesiredAimAt);
		MoveTurretTowards(&vDesiredAimAt);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector* AimDirection)
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate barrel"), *GetOwner()->GetName());  return; }
	// Calculate the movement required
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector* AimDirection)
{
	if (!ensure(Turret)) { UE_LOG(LogTemp, Warning, TEXT("%s unable to locate turret"), *GetOwner()->GetName());  return; }
	// Calculate the movement required
	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;
	Turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::FireProjectile()
{
	if (Barrel && FiringStatus != EFiringStatus::Reloading) {
		LastTimeFired = GetWorld()->GetTimeSeconds();

		//Spawn a projectile at the Socket on the barrel
		FVector Startpoint = Barrel->GetSocketLocation(FName("ProjectileLaunchPoint"));
		FRotator Rotation = Barrel->GetForwardVector().Rotation();
		FActorSpawnParameters SpawnInfo;
		if (!ensure(ProjectileBlueprint)) {
			auto time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Error, TEXT("%f: - Projectile blueprint not available!"), time);
			return;
		}
		AProjectile* MyProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Startpoint, Rotation, SpawnInfo);
		MyProjectile->LaunchProjectile(ProjectileVelocity);
	}
}

