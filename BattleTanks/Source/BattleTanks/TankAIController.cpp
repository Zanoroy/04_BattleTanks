// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controler: Begin play"));

	GetControlledTank();
}

ATank* ATankAIController::GetControlledTank() const {
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

ATank * ATankAIController::GetPlayerTank() const
{

	GetWorld()->GetPlayerController()
	return nullptr;
}

