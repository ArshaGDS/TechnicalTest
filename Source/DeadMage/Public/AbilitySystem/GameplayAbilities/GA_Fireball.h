// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Fireball.generated.h"


UCLASS()
class DEADMAGE_API UGA_Fireball : public UGameplayAbility
{
	GENERATED_BODY()
	
	uint8 Counter { 0 };
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	// Name of the related section anim attack in anim montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireballAttack|Animation")
	TArray<FName> AnimSectionNames;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	uint8 GetComboAttackNumber();

	UFUNCTION(BlueprintCallable)
	void PerformAttack(const FName SpawnSocketName);

private:
	
	uint8 ComboAttackNumber { 0 };
};
