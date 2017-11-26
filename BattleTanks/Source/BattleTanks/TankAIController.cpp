// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto TargetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!TargetTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to locate target tank!!! What do I do now. I am a tank with no purpose"));
	}

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to locate self tank!!! What do I do now. I am a tank with no purpose"));
	}

	MoveToActor(TargetTank, AcceptanceRadius);

	ControlledTank->AimAt(TargetTank->GetActorLocation());

	ControlledTank->FireProjectile();
}


