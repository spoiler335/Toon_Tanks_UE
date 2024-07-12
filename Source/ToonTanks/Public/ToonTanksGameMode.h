// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *deadActor);

protected:
	virtual void BeginPlay() override;

private:
	class ATank *tank;
	class AToonTanksPlayerController *playerController;

	float startDelay = 3.0f; 

	void HandleGameStart();

};
