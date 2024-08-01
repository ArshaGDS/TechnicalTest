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
	
	uint8 Counter { 0 };
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FireballAttack")
	float FinisherDelay { 1.3f };

	UPROPERTY(EditDefaultsOnly, Category = "FireballAttack")
	FName StartFinisherSectionName {};
	
	// Name of the related section anim attack in anim montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireballAttack|Animation")
	TArray<FName> AnimSectionNames;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireballAttack|Animation")
	TSubclassOf<APooledActor> PooledActorClass;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	uint8 GetComboAttackNumber();

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetPlayer();
	
	UFUNCTION(BlueprintCallable)
	bool IsFinisherAttack();

	UFUNCTION(BlueprintCallable)
	void PerformAttack();

	// Trigger in blueprint child class to play animation 
	UFUNCTION(BlueprintImplementableEvent, Category = "FireballAttack|Animation", DisplayName = "PlayAttackMontage", meta=(ScriptName = "PlayAttackMontage"))
	void K2_PlayAttackMontage(FName AnimSectionName);

private:

	FTimerHandle FinisherTimerHandle;
	
	uint8 ComboAttackNumber { 0 };

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacterPtr { nullptr };

	void SpawnProjectile(const bool IsFinisher);
	void FinisherTimer();
};
