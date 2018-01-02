// Copyright Bruce Quinton (ish)

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float);
	
	UPROPERTY(VisibleAnywhere, category = "Setup")
	UStaticMeshComponent *CollisionMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, category = "Setup")
	UParticleSystemComponent *LaunchBlast = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
};
