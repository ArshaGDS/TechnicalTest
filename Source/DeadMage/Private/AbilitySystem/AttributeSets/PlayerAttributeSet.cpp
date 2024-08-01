// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetPlayerHealthAttribute())
	{
		SetPlayerHealth(FMath::Clamp(GetPlayerHealth(), 0.f, GetPlayerMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetPlayerArcanaAttribute())
	{
		SetPlayerArcana(FMath::Clamp(GetPlayerArcana(), 0.f, GetPlayerMaxArcana()));
	}
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, PlayerHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, PlayerMaxHealth, COND_None, REPNOTIFY_Always)
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, PlayerArcana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, PlayerMaxArcana, COND_None, REPNOTIFY_Always)
}

void UPlayerAttributeSet::OnRep_PlayerHealth(FGameplayAttributeData& OldPlayerHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, PlayerHealth, OldPlayerHealth);
}

void UPlayerAttributeSet::OnRep_PlayerMaxHealth(FGameplayAttributeData& OldPlayerMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, PlayerMaxHealth, OldPlayerMaxHealth);
}

void UPlayerAttributeSet::OnRep_PlayerArcana(FGameplayAttributeData& OldPlayerArcana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, PlayerArcana, OldPlayerArcana);
}

void UPlayerAttributeSet::OnRep_PlayerMaxArcana(FGameplayAttributeData& OldPlayerMaxArcana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, PlayerMaxArcana, OldPlayerMaxArcana);
}