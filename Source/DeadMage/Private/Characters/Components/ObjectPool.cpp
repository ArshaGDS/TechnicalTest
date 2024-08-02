// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/ObjectPool.h"

#include "Actors/PooledActor.h"

UObjectPool::UObjectPool()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UObjectPool::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() == NM_DedicatedServer && (GetOwner()->GetLocalRole() == ROLE_Authority || GetOwner()->GetLocalRole() == ROLE_SimulatedProxy))
	{
		// No need for initialization
		return;
	}
	
	InitializePool();
}

APooledActor* UObjectPool::FindFirstAvailableActor()
{
	for (uint8 Index = 0 ; Index < ObjectPool.Num() ; Index++)
	{
		if (ObjectPool[Index]->IsValidLowLevel() && !ObjectPool[Index]->bInUse)
		{
			return ObjectPool[Index];
		}
	}

	return nullptr;
}

APooledActor* UObjectPool::SpawnActorFromPool(const FTransform& SpawnTransform)
{
	APooledActor* PooledActor = FindFirstAvailableActor();
	if (PooledActor)
	{
		PooledActor->SetActorTransform(SpawnTransform);
		PooledActor->SetInUse(true);
		return  PooledActor;
	}

	return nullptr;
}

void UObjectPool::InitializePool()
{
	if (!GetWorld() || !GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Pool initialization failed"), __FUNCTION__);
		return;
	}
	
	ObjectPool.Reserve(PoolSize);
	for (uint8 Index = 0 ; Index < PoolSize ; Index++)
	{
		ObjectPool.Insert (
		GetWorld()->SpawnActorDeferred<APooledActor>(PooledActorClass,
				   FTransform(), GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn),
				   Index
		);
		
		if (ObjectPool[Index])
		{
			// Finish spawn and set location at (0, 0, 0) in the world 
			ObjectPool[Index]->FinishSpawning(FTransform());
		}
	}
}

