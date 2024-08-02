// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DataAssets/CharacterAbilitiesDataAsset.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	MinNetUpdateFrequency = 33;
	NetUpdateFrequency = 100;
	
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	if (AbilitySystem)
	{
		AbilitySystem->SetIsReplicated(true);
	}
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server side
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
		SetOwner(NewController);
		
		ApplyStartupEffects();
		GiveAbilities();
	}
}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client side
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
		UE_LOG(LogTemp, Error, TEXT("[%hs]"), __FUNCTION__);
	}
}

// Interface
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

// Interfaces
ACharacterBase* ACharacterBase::GetCharacterBase_Implementation()
{
	return this;
}

void ACharacterBase::SendGameplayEventToActor(ACharacterBase* Character, const FGameplayTag EventTag)
{
	FGameplayEventData Payload;
	Payload.Instigator = Character;
	Payload.EventTag = EventTag;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Payload.EventTag, Payload);
}

void ACharacterBase::GiveAbilities() const
{
	// Server side
	if (AbilitySystem && CharacterDataAsset)
	{
		for (const TSubclassOf<UGameplayAbility> DefaultAbility : CharacterDataAsset->CharacterData.Abilities)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
		}
	}
}

void ACharacterBase::ApplyStartupEffects()
{
	// Server side
	if (CharacterDataAsset)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (const TSubclassOf<UGameplayEffect> Effect: CharacterDataAsset->CharacterData.Effects)
		{
			ApplyGameplayEffectsToSelf(Effect, EffectContext);
		}
	}
}

bool ACharacterBase::ApplyGameplayEffectsToSelf(const TSubclassOf<UGameplayEffect>& Effect, const FGameplayEffectContextHandle& InEffectContext)
{
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(Effect, DEFAULT_EFFECT_LEVEL, InEffectContext);
	if (SpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		return ActiveGEHandle.WasSuccessfullyApplied();
	}
	
	return false;
}