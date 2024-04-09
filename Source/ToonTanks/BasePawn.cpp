// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComponent = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComponent;

	baseMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsuleComponent);

	turretMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector toTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0, toTarget.Rotation().Yaw, 0);
	FRotator targetRotation = FMath::RInterpTo(turretMesh->GetComponentRotation(), lookAtRotation, GetWorld()->DeltaTimeSeconds, 25.f);
	turretMesh->SetWorldRotation(targetRotation);
}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();
	// DrawDebugSphere(GetWorld(), spawnLocation, 25.f, 12, FColor::Red, false, 2.f);
	auto projectile = GetWorld()->SpawnActor<AProjectile>(projectilePrefab, spawnLocation, spawnRotation);
	projectile->SetOwner(this);
}