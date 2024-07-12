// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *deadActor)
{
    if (deadActor == tank)
    {
        tank->HandleDestruction();
        if (playerController)
            playerController->SetPlayerEnabledState(false);
    }
    else if (auto destroyedTower = Cast<ATower>(deadActor))
    {
        destroyedTower->HandleDestruction();
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
