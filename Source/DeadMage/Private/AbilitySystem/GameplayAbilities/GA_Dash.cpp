// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/GA_Dash.h"

#include "Characters/PlayerCharacter.h"
#include "Interfaces/PlayerCharacterInterface.h"

void UGA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (AvatarActor && AvatarActor->Implements<UPlayerCharacterInterface>())
	{
		APlayerCharacter* PlayerCharacter = IPlayerCharacterInterface::Execute_GetPlayerCharacter(AvatarActor);
		PerformDash(PlayerCharacter);
	}
}

void UGA_Dash::PerformDash(APlayerCharacter* PlayerCharacter) const
{
	const FVector DashVector = PlayerCharacter->GetActorForwardVector() * DashImpuls;
	PlayerCharacter->LaunchCharacter(DashVector, true, false);
}
