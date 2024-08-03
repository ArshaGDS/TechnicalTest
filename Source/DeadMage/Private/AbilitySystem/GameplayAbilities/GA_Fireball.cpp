// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/GA_Fireball.h"

#include "AbilitySystemComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/Components/CombatComponent.h"

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Register delegate for detect attack state
	GetPlayer()->GetPlayerCombatComponent()->OnStartedAttack.AddUObject(this, &UGA_Fireball::OnStartedAttack);
	GetPlayer()->GetPlayerCombatComponent()->OnFinishedAttack.AddUObject(this, &UGA_Fireball::OnFinishedAttack);
	CommitAbilityCost(Handle, ActorInfo, ActivationInfo);
	PerformAttack();
}

void UGA_Fireball::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// Unregister delegate for detect attack state
	GetPlayer()->GetPlayerCombatComponent()->OnStartedAttack.RemoveAll(this);
	GetPlayer()->GetPlayerCombatComponent()->OnFinishedAttack.RemoveAll(this);
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
	GetPlayer()->GetPlayerCombatComponent()->Attack();
}

void UGA_Fireball::OnStartedAttack(const uint8 AttackNumber, const bool bIsFinisher)
{
	if (bIsFinisher)
	{
		const uint8 AnimSectionNameIndex = AnimSectionNames.Num() - 2;
		
		// Play first part of finisher animation 
		K2_PlayAttackMontage( AnimSectionNames[ AnimSectionNameIndex ] );
	}
}

void UGA_Fireball::OnFinishedAttack(const uint8 AttackNumber, const bool bIsFinisher)
{
	if (bIsFinisher)
	{
		// Play second part of finisher animation
		K2_PlayAttackMontage( AnimSectionNames.Last() );
	}
	else
	{
		const uint8 AnimSectionNameIndex = AttackNumber - 1;
        	
		// If index in array range
		if (AnimSectionNameIndex < AnimSectionNames.Num() && AnimSectionNameIndex > -1)
		{
			K2_PlayAttackMontage(AnimSectionNames[ AnimSectionNameIndex ]);
		}
		
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
	}
}