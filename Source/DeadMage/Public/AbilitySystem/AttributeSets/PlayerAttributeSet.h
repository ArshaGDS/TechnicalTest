// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DEADMAGE_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerHealth)
	FGameplayAttributeData PlayerHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, PlayerHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerMaxHealth)
	FGameplayAttributeData PlayerMaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, PlayerMaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerArcana)
	FGameplayAttributeData PlayerArcana;
	ATTRIBUTE_ACCESSORS(ThisClass, PlayerArcana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerMaxArcana)
	FGameplayAttributeData PlayerMaxArcana;
	ATTRIBUTE_ACCESSORS(ThisClass, PlayerMaxArcana)

protected:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_PlayerHealth(FGameplayAttributeData& OldPlayerHealth);

	UFUNCTION()
	virtual void OnRep_PlayerMaxHealth(FGameplayAttributeData& OldPlayerMaxHealth);

	UFUNCTION()
	virtual void OnRep_PlayerArcana(FGameplayAttributeData& OldPlayerArcana);

	UFUNCTION()
	virtual void OnRep_PlayerMaxArcana(FGameplayAttributeData& OldPlayerMaxArcana);
};
