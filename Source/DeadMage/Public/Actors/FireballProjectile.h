// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "FireballProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DEADMAGE_API AFireballProjectile : public APooledActor
{
	GENERATED_BODY()

public:

	AFireballProjectile();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fireball|Movement")
	float FireballVelocity { 700.f };
	
	virtual void BeginPlay() override;

	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);

	virtual void OnInUse(const bool InUse) override;
};
