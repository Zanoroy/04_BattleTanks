// Copyright Bruce Quinton (ish)

#pragma once

#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Public/TimerManager.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	void LaunchProjectile(float);
	
	UPROPERTY(VisibleAnywhere, category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, category = "Components")
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, category = "Components")
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void TimerExpired();

	UPROPERTY(EditAnywhere, category = "Setup")
	float DestoryDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20.f;


private:	
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
};
