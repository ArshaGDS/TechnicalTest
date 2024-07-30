// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCharacterAbilitiesDataAsset;
class UAbilitySystemComponent;

// To avoid the magic number
#define DEFAULT_EFFECT_LEVEL 1

UCLASS()
class DEADMAGE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ACharacterBase();

protected:

	void GiveAbilities() const;
	void ApplyStartupEffects();
	
	void SendGameplayEventToActor(ACharacterBase* Character, const FGameplayTag EventTag);
	bool ApplyGameplayEffectsToSelf(const TSubclassOf<UGameplayEffect>& Effect,
	                                const FGameplayEffectContextHandle& InEffectContext);

private:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(EditDefaultsOnly, Category = "Player|DataAssets")
	TObjectPtr<UCharacterAbilitiesDataAsset> CharacterDataAsset;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
