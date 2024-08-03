// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "GA_Fireball.generated.h"


class APooledActor;

UCLASS()
class DEADMAGE_API UGA_Fireball : public UGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	
	// Name of the related section anim attack in anim montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireballAttack|Animation")
	TArray<FName> AnimSectionNames;
	
	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetPlayer();
	
	UFUNCTION(BlueprintCallable)
	void PerformAttack();

	// Trigger in blueprint child class to play animation 
	UFUNCTION(BlueprintImplementableEvent, Category = "FireballAttack|Animation", DisplayName = "PlayAttackMontage", meta=(ScriptName = "PlayAttackMontage"))
	void K2_PlayAttackMontage(FName AnimSectionName);

private:
	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacterPtr { nullptr };
	
	void OnStartedAttack(const uint8 AttackNumber, const bool bIsFinisher);
	void OnFinishedAttack(const uint8 AttackNumber, const bool bIsFinisher);
};
