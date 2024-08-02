// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/GA_Fireball.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Actors/FireballProjectile.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/Components/ObjectPool.h"

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PerformAttack();
}

APlayerCharacter* UGA_Fireball::GetPlayer()
{
	if (PlayerCharacterPtr) return PlayerCharacterPtr;
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor && AvatarActor->Implements<UPlayerCharacterInterface>())
	{
		PlayerCharacterPtr = IPlayerCharacterInterface::Execute_GetPlayerCharacter(AvatarActor);

		return PlayerCharacterPtr;
	}

	return nullptr;
}

void UGA_Fireball::PerformAttack()
{
	if (!IsFinisherAttack())
	{
		SpawnProjectile(false);
		const uint8 AnimSectionNameIndex = GetPlayer()->GetComboAttackNumber() - 1;

		// If index in array range
		if (AnimSectionNameIndex < AnimSectionNames.Num() && AnimSectionNameIndex > -1)
		{
			K2_PlayAttackMontage(AnimSectionNames[ AnimSectionNameIndex ]);
			K2_CommitAbilityCost();
		}
		K2_EndAbility();
	}
	else
	{
		if (GetWorld())
		{
			// Start finisher part of cycle
			const uint8 FinisherPart1Index = AnimSectionNames.Num() - 2;
			K2_PlayAttackMontage( AnimSectionNames[FinisherPart1Index] );
			// Delay for charging attack
			GetWorld()->GetTimerManager().SetTimer(FinisherTimerHandle, this, &UGA_Fireball::FinisherTimer, FinisherDelay);
		}
	}
}

void UGA_Fireball::SpawnProjectile(const bool IsFinisher)
{
	FTransform SpawnTransform = GetPlayer()->GetActorTransform();
	const FVector Location = GetPlayer()->GetActorLocation() + (GetPlayer()->GetActorForwardVector() * 100);
	SpawnTransform.SetLocation(Location);

	APooledActor* Projectile = GetPlayer()->ObjectPoolComponent->SpawnActorFromPool(SpawnTransform);
	if (Projectile && Projectile->Implements<UFireballInterface>())
	{
		IFireballInterface::Execute_SetFireballAttackState(Projectile, IsFinisher);
	}
}

void UGA_Fireball::FinisherTimer()
{
	UE_LOG(LogTemp, Error, TEXT("[%hs]"), __FUNCTION__);
	GetWorld()->GetTimerManager().PauseTimer(FinisherTimerHandle);
	FinisherTimerHandle.Invalidate();
	K2_PlayAttackMontage( AnimSectionNames.Last() );
	SpawnProjectile(true);
	K2_CommitAbilityCost();
	K2_EndAbility();
	// Cycle is ended
}

uint8 UGA_Fireball::GetComboAttackNumber()
{
	ComboAttackNumber = GetPlayer()->GetComboAttackNumber();
	return ComboAttackNumber;
}

bool UGA_Fireball::IsFinisherAttack()
{
	return GetPlayer()->GetMaxComboAttack() == GetPlayer()->GetComboAttackNumber();
}
