// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controler: Begin play"));

	GetControlledTank();
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* MyTank = Cast<ATank>(GetPawn());

	if (MyTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Tank: %s"), *MyTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get possessed Tank"));
	}

	return MyTank;

}
