// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireballProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
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
		ProjectileMovementComponent->SetIsReplicated(true);
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
}

void AFireballProjectile::OnInUse(const bool InUse)
{
	Super::OnInUse(InUse);

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity = InUse ? GetActorForwardVector() * FireballVelocity : FVector::ZeroVector ;
	}
}

void AFireballProjectile::SetFireballAttackState_Implementation(bool IsFinisher)
{
	bIsFinisher = IsFinisher;
}

void AFireballProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetInUse(false);

	// Apply damage on overlapped actor
	ApplyDamageEffectOnHitedActor(OtherActor);
}

void AFireballProjectile::ApplyDamageEffectOnHitedActor(AActor* HitedActor)
{
	if (HitedActor && HitedActor->Implements<UAbilitySystemInterface>())
	{
		UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitedActor);

		if (bIsFinisher)
		{
			ApplyEffectsToActor(AbilitySystem, FinisherDamageEffect);
			bIsFinisher = false;
		}
		else
		{
			ApplyEffectsToActor(AbilitySystem, DamageEffect);
		}
		SetInUse(false);
	}
}

FGameplayEffectContextHandle AFireballProjectile::ApplyEffectsToActor(UAbilitySystemComponent* TargetAbilitySystemComponent,
                                                                      const TSubclassOf<UGameplayEffect>& Effect) const
{
	const FGameplayEffectContextHandle EffectContext = TargetAbilitySystemComponent->MakeEffectContext();

	const FGameplayEffectSpecHandle SpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		const bool bWasSuccessful = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()).WasSuccessfullyApplied();

		if (!bWasSuccessful)
		{
			ABILITY_LOG(Log, TEXT("[Gamelay ability base] ActivateAbility: Ability %s failed to apply startup effect %s."), *GetName(), *GetNameSafe(Effect));
		}
	}
	
	return EffectContext;
}