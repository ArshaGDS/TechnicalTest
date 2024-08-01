﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PooledActor.h"

APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APooledActor::BeginPlay()
{
	Super::BeginPlay();

	SetInUse(false);
}

void APooledActor::SetInUse(const bool InUse)
{
	bInUse = InUse;
	SetActorEnableCollision(InUse);
	SetActorHiddenInGame(InUse);

	if (InUse && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::ReturnToPool, TimeToLive, false);
	}

	OnInUse(InUse);
}

void APooledActor::ReturnToPool()
{
	TimerHandle.Invalidate();
	SetInUse(false);
}
