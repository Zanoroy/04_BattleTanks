// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// UPROPERTY(BlueprintAssignable, Category = "Test")
	FTankDelegate OnDeath;

private:	
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category ="Setup")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Inilalised in Beginplay

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
