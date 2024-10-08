// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::CheckFireCondition, fireRate, true);
}

void ATower::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    if (IsTankInFireRange())
        RotateTurret(playerTank->GetActorLocation());
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition()
{
    if (!playerTank)
        return;
    if (!playerTank->bIsAlive)
        return;
    UE_LOG(LogTemp, Warning, TEXT("CheckFireCondition"));
    if (IsTankInFireRange())
        Fire();
}

bool ATower::IsTankInFireRange()
{
    if (!playerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
        return false;
    }

    return FVector::Dist(GetActorLocation(), playerTank->GetActorLocation()) <= fireRange;
}