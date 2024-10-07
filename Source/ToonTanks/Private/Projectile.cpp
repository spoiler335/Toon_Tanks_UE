// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke-Trail"));
	trailParticles->SetupAttachment(RootComponent);

	projectileMovement->InitialSpeed = 1300.f;
	projectileMovement->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (lauchSound)
		UGameplayStatics::PlaySoundAtLocation(this, lauchSound, GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent *hitComponent, AActor *otherActor, UPrimitiveComponent *otherComponent, FVector impulse, const FHitResult &hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));

	auto myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		Destroy();
		return;
	}
	auto myOwnerInstigator = myOwner->GetInstigatorController();
	auto damageType = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, myOwnerInstigator, this, damageType);
		if (hitparticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, hitparticles, GetActorLocation(), GetActorRotation());

		if (hitSound)
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());

		if (hitCameraShake)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShake);
	}

	Destroy();
}