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
        destroyedTower->HandleDestruction();
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (playerController)
    {
        playerController->SetPlayerEnabledState(false);

        FTimerHandle playerEnabledTimerHandler;
        FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(playerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(playerEnabledTimerHandler, timerDelegate, startDelay, false);
    }
}
