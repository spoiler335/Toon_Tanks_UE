// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float deltaTime) override;
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	ATank* playerTank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float fireRange = 500.f;

	FTimerHandle fireRateTimerHandle;
	float fireRate = 2.f;
	
	void CheckFireCondition();
	bool IsTankInFireRange();
};
