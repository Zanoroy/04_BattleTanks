// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "TankAIController.generated.h"

class ATank; // Forward Decleration
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Public to child classes ONLY! (such as Blueprints)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
