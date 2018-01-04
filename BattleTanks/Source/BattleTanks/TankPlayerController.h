// Copyright Bruce Quinton (ish)
/// #include "Components/ActorComponent.h"
/// #include "GameFramework/Actor.h"


#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank; // Forward Declaration
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
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	virtual void SetPawn(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	void AimTowardCrosshair();

	// Start the tank barrel moving toward the where the crosshair is in the world..
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnTankDeath();

	UPROPERTY(EditAnywhere)
	float TankRange = 1000000.0f;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

};
