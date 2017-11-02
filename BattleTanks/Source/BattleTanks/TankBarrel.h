// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere, category = Setup)
	float MaxDegressPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, category = Setup)
	float MaxElevation = 40.0f;

	UPROPERTY(EditAnywhere, category = Setup)
	float MinElevation = 0.0f;
};
