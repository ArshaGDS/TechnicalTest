// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

#include "AbilitySystemComponent.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	if (AbilitySystem)
	{
		AbilitySystem->ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	}
}