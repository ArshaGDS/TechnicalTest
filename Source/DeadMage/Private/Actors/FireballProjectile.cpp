// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireballProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFireballProjectile::AFireballProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::AFireballProjectile::OnOverlap);	
}

void AFireballProjectile::OnInUse(const bool InUse)
{
	Super::OnInUse(InUse);

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity = InUse ? GetActorForwardVector() * FireballVelocity : FVector::ZeroVector ;
	}
}

void AFireballProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetInUse(false);
}