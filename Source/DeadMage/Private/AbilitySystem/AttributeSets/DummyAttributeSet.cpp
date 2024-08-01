// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/DummyAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UDummyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDummyHealthAttribute())
	{
		SetDummyHealth(FMath::Clamp(GetDummyHealth(), 0.f, GetDummyMaxHealth()));
	}
}

void UDummyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDummyAttributeSet, DummyHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDummyAttributeSet, DummyMaxHealth, COND_None, REPNOTIFY_Always)
}

void UDummyAttributeSet::OnRep_DummyHealth(FGameplayAttributeData& OldDummyHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDummyAttributeSet, DummyHealth, OldDummyHealth);
}

void UDummyAttributeSet::OnRep_DummyMaxHealth(FGameplayAttributeData& OldDummyMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDummyAttributeSet, DummyMaxHealth, OldDummyMaxHealth);
}
