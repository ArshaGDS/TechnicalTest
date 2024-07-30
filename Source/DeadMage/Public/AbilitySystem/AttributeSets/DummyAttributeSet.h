// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DummyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DEADMAGE_API UDummyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DummyHealth)
	FGameplayAttributeData DummyHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, DummyHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DummyMaxHealth)
	FGameplayAttributeData DummyMaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, DummyMaxHealth)

protected:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_DummyHealth(FGameplayAttributeData& OldDummyHealth);

	UFUNCTION()
	virtual void OnRep_DummyMaxHealth(FGameplayAttributeData& OldDummyMaxHealth);
};
