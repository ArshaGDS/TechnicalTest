﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireballProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFireballProjectile::AFireballProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	MinNetUpdateFrequency = 33;
	NetUpdateFrequency = 100;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->ProjectileGravityScale = 0.f;
		ProjectileMovementComponent->bInitialVelocityInLocalSpace = false;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.f;
		ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	}
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	if (SphereCollision)
	{
		RootComponent = SphereCollision;
	}
}

void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::AFireballProjectile::OnOverlap);
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * FireballVelocity;
}

void AFireballProjectile::OnInUse(const bool InUse)
{
	Super::OnInUse(InUse);

	if (ProjectileMovementComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("[%hs], %i"), __FUNCTION__, InUse);
		//ProjectileMovementComponent->Velocity = InUse ? GetActorForwardVector() * FireballVelocity : FVector::ZeroVector ;
	}
}

void AFireballProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//SetInUse(false);

	// Apply damage on overlapped actor
	UE_LOG(LogTemp, Display, TEXT("[%hs]"), __FUNCTION__);
}