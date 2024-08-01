// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class DEADMAGE_API APooledActor : public AActor
{
	GENERATED_BODY()

public:
	
	bool bInUse { false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PooledActor")
	float TimeToLive { 3.f };

	APooledActor();
	
	void SetInUse(const bool InUse);
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnInUse(const bool InUse) {}

private:

	FTimerHandle TimerHandle;

	// Call after specific delay to bring back actor to pool
	void ReturnToPool();
};
