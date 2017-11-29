// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
		void Rotate(float RelativeSpeed);

		UPROPERTY(EditAnywhere, category = Setup)
		float MaxDegressPerSecond = 20.0f;
	
};
