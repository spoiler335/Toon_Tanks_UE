// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShakeBase.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Comabat")
	UStaticMeshComponent *projectileMesh;

	UPROPERTY(VisibleAnyWhere, Category = "Movement")
	UProjectileMovementComponent *projectileMovement;

	UPROPERTY(EditAnyWhere)
	float damage = 50.f;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	UParticleSystem *hitparticles;

	UPROPERTY(VisibleAnyWhere, Category = "Combat")
	UParticleSystemComponent *trailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *lauchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *hitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> hitCameraShake;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *hitComponent, AActor *otherActor, UPrimitiveComponent *otherComponent, FVector impulse, const FHitResult &hit);
};
