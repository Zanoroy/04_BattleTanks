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
	Locked,
	NoAmmo
};

//// Forward declaration
//class UTankBarrel; 
//class UTankTurret;

// Hold's properties for the Tank Barrel.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Initalise(UTankBarrel * Barrel, UTankTurret * Turret);
	
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ProjectileVelocity = 4000.0f;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeinSeconds = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	EFiringStatus GetFiringState() const;

private:
	void MoveBarrelTowards(FVector*);
	void MoveTurretTowards(FVector*);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	int RoundsLeft = 3;

	//bool isReloaded = false;
	double LastTimeFired = 0;
	bool IsBarrelMoving();
	FVector vDesiredAimAt;

	// Called every frame
	virtual void TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
};