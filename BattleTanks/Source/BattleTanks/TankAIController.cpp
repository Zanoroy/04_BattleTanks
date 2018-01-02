// Copyright Bruce Quinton (ish)

#include "TankAIController.h"
#include "TankAimingComponent.h"
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

	if (!ensure(TargetTank))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to locate target tank!!! What do I do now. I am a tank with no purpose"));
		return;
	}

	if (!ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to locate self tank!!! What do I do now. I am a tank with no purpose"));
		return;
	}

	MoveToActor(TargetTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(TargetTank->GetActorLocation());

	// Only fire when we are locked on the target!
	if(AimingComponent->GetFiringState() == EFiringStatus::Locked)
		AimingComponent->FireProjectile();
}


