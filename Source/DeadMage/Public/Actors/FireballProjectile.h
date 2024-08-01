// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "PooledActor.h"
#include "FireballProjectile.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DEADMAGE_API AFireballProjectile : public APooledActor
{
	GENERATED_BODY()

public:

	AFireballProjectile();

	FORCEINLINE void SetIsFinisher(const bool bFinisher) { bIsFinisher = bFinisher; }

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fireball|Movement")
	float FireballVelocity { 700.f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;

	// Finisher damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball|Damage")
	TSubclassOf<UGameplayEffect> FinisherDamageEffect;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void OnInUse(const bool InUse) override;

private:
	
	void ApplyDamageEffectOnHitedActor(AActor* HitedActor);
	
	FGameplayEffectContextHandle ApplyEffectsToActor(UAbilitySystemComponent* TargetAbilitySystemComponent,
	                                                 const TSubclassOf<UGameplayEffect>& Effect) const;

	bool bIsFinisher { false };
};
