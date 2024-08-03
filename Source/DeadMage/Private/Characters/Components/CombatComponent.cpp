// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/CombatComponent.h"

#include "Actors/PooledActor.h"
#include "Characters/Components/ObjectPool.h"
#include "Characters/PlayerCharacter.h"
#include "Interfaces/FireballInterface.h"
#include "Net/UnrealNetwork.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponent::Attack()
{
	const double CurrentGameSecond = GetWorld()->GetTimeSeconds();
	if (CurrentGameSecond - LastAttackSecond > MaxDelayBetweenAttacks)
	{
		// Reset the cycle
		ResetTheCombatCycle();
	}
	
	// Save current game second for next cycle
	LastAttackSecond = CurrentGameSecond;

	IncreaseCurrentAttackNumber();
	
	OnStartedAttack.Broadcast(CurrentAttackNumber, IsFinisherAttack());
	
	if (!IsFinisherAttack())
	{
		SpawnProjectile(false);
	}
	else
	{
		if (GetWorld())
		{
			// Delay for charging attack
			GetWorld()->GetTimerManager().SetTimer(FinisherTimerHandle, this, &UCombatComponent::FinisherFunction, FinisherDelay);
		}
	}
}

void UCombatComponent::FinisherFunction()
{
	SpawnProjectile(true);
	ResetTheCombatCycle();
	GetWorld()->GetTimerManager().PauseTimer(FinisherTimerHandle);
	FinisherTimerHandle.Invalidate();
	// Cycle is ended
}

void UCombatComponent::SpawnProjectile(const bool bIsFinisher)
{
	FTransform SpawnTransform = GetPlayer()->GetActorTransform();
	const FVector Location = GetPlayer()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 100);
	SpawnTransform.SetLocation(Location);

	APooledActor* Projectile = GetPlayer()->ObjectPoolComponent->SpawnActorFromPool(SpawnTransform);
	if (Projectile && Projectile->Implements<UFireballInterface>())
	{
		IFireballInterface::Execute_SetFireballAttackState(Projectile, bIsFinisher);
	}

	OnFinishedAttack.Broadcast(CurrentAttackNumber, bIsFinisher);
}

void UCombatComponent::ResetTheCombatCycle()
{
	CurrentAttackNumber = 0;
	LastAttackSecond = 0;
}

APlayerCharacter* UCombatComponent::GetPlayer()
{
	if (PlayerCharacterPtr) return PlayerCharacterPtr;
	
	if (GetOwner() && GetOwner()->Implements<UPlayerCharacterInterface>())
	{
		PlayerCharacterPtr = IPlayerCharacterInterface::Execute_GetPlayerCharacter(GetOwner());
		return PlayerCharacterPtr;
	}

	return nullptr;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, CurrentAttackNumber);
}