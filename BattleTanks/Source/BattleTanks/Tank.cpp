// Copyright Bruce Quinton (ish)

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTrack.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect the Pointer, it is part of the constructor
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	//TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	//TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetLeftTrackReference(UTankTrack * TrackToSet)
{
	LeftTrack = TrackToSet;
}

void ATank::SetRightTrackReference(UTankTrack * TrackToSet)
{
	RightTrack = TrackToSet;
}

void ATank::FireProjectile()
{
	isReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeinSeconds;
	if (TankAimingComponent && TankAimingComponent->FiringStatus == EFiringStatus::Reloading)
		TankAimingComponent->FiringStatus = EFiringStatus::Aiming;

	if (Barrel && isReloaded) {
		//Spawn a projectile at the Socket on the barrel
		FVector Startpoint = Barrel->GetSocketLocation(FName("ProjectileLaunchPoint"));
		FRotator Rotation = Barrel->GetForwardVector().Rotation();
		FActorSpawnParameters SpawnInfo;

		if (!ProjectileBlueprint) {
			auto time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Error, TEXT("%f: - Projectile blueprint not available!"), time);
			return;
		}

		AProjectile* MyProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Startpoint, Rotation, SpawnInfo);
		MyProjectile->LaunchProjectile(ProjectileVelocity);

		LastTimeFired = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if(TankAimingComponent)
		TankAimingComponent->AimAt(HitLocation, ProjectileVelocity);

}


