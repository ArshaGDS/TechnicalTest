// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/GA_Fireball.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Characters/PlayerCharacter.h"

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
	// Launch projectile

	//EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_Fireball::PerformAttack()
{
	
}

uint8 UGA_Fireball::GetComboAttackNumber()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor && AvatarActor->Implements<UPlayerCharacterInterface>())
	{
		const APlayerCharacter* Player = IPlayerCharacterInterface::Execute_GetPlayerCharacter(AvatarActor);
		
		// Get attack state
		ComboAttackNumber = Player->GetComboAttackNumber();
		
		return ComboAttackNumber;
	}

	return ComboAttackNumber;
}
