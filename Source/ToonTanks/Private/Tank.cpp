// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(springArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    tankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float value)
{
    FVector movememt = FVector(value * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0, 0);
    AddActorLocalOffset(movememt, true);
}

void ATank::Turn(float value)
{
    FRotator rotation = FRotator(0, value * rotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0);
    AddActorLocalRotation(rotation, true);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    if (tankPlayerController)
    {
        FHitResult hit;
        tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);
        RotateTurret(hit.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bIsAlive = false;
}
