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
        GameOver(false);
    }
    else if (auto destroyedTower = Cast<ATower>(deadActor))
    {
        destroyedTower->HandleDestruction();
        --targetTowers;
        if (targetTowers <= 0)
            GameOver(true);
    }
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

    StartGame();
    targetTowers = GetTowerCount();

    if (playerController)
    {
        playerController->SetPlayerEnabledState(false);

        FTimerHandle playerEnabledTimerHandler;
        FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(playerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(playerEnabledTimerHandler, timerDelegate, startDelay, false);
    }
}

int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor *> foundTowers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), foundTowers);
    return foundTowers.Num();
}
