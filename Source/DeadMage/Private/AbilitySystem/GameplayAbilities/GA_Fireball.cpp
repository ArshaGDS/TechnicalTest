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
	
}

void UGA_Fireball::PerformAttack(const FName SpawnSocketName)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor && AvatarActor->Implements<UPlayerCharacterInterface>())
	{
		const APlayerCharacter* Player = IPlayerCharacterInterface::Execute_GetPlayerCharacter(AvatarActor);
		
		//Player->ObjectPoolComponent->SpawnActorFromPool(Player->GetMesh()->GetSocketTransform(SpawnSocketName));
		/*FTransform Transform;
		Transform.SetLocation(Player->GetActorLocation());
		Player->ObjectPoolComponent->SpawnActorFromPool(Transform);*/
		
		AFireballProjectile* FireballProjectile = GetWorld()->SpawnActorDeferred<AFireballProjectile>(PooledActorClass,
			   Player->GetActorTransform(), GetAvatarActorFromActorInfo(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		if (FireballProjectile)
		{
			FireballProjectile->FinishSpawning(Player->GetActorTransform());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs]"), __FUNCTION__);
	}
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
