// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();
    playerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!playerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *playerTank->GetName());
}

void ATower::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    float distance = FVector::Dist(GetActorLocation(), playerTank->GetActorLocation());
    if (distance <= fireRange)
    {
        RotateTurret(playerTank->GetActorLocation());
    }
}
