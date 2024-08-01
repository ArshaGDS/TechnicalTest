// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"


class APooledActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADMAGE_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:

	UObjectPool();

	APooledActor* SpawnActorFromPool(const FTransform& SpawnTransform);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PoolOptions")
	uint8 PoolSize { 9 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PoolOptions")
	TSubclassOf<APooledActor> PooledActorClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "PoolOptions")
	TArray<APooledActor*> ObjectPool;
	
	virtual void BeginPlay() override;

	APooledActor* FindFirstAvailableActor();

private:

	// Spawn pooled actors and cache in the pool 
	void InitializePool();
};
