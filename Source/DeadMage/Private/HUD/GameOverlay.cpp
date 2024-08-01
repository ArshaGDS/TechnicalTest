// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOverlay.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "Characters/PlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerCharacterInterface.h"

void UGameOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const bool bIsValidNecessaryClasses = GetOwningPlayer() && GetOwningPlayer()->GetCharacter() && GetWorld(); 
	
	if (bIsValidNecessaryClasses)
	{
		InitializeUIData();
		RegisterAllInformationCallbacks();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Initialization faild, One of necessary classes is NOT valid."), __FUNCTION__);
	}
}

void UGameOverlay::InitializeUIData()
{
	const float MaxHealth = GetPlayer()->GetPlayerAttributeSet()->GetPlayerMaxHealth();
	SetPlayerHealth(MaxHealth, MaxHealth);
	
	const float MaxArcana = GetPlayer()->GetPlayerAttributeSet()->GetPlayerMaxArcana();
	SetPlayerArcana(MaxArcana, MaxArcana);
}

void UGameOverlay::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (GetPlayer())
	{
		UnregisterAllInformationCallbacks();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Destruction faild, One of necessary pointers is NOT valid."), __FUNCTION__);
	}
}

APlayerCharacter* UGameOverlay::GetPlayer()
{
	if (CurrentPlayer) return CurrentPlayer;
	
	// Get CurrentPlayer
	ACharacter* ControlledCharacter = GetOwningPlayer()->GetCharacter();

	if (ControlledCharacter && ControlledCharacter->Implements<UPlayerCharacterInterface>())
	{
		CurrentPlayer = IPlayerCharacterInterface::Execute_GetPlayerCharacter(ControlledCharacter);
		return CurrentPlayer;
	}

	return nullptr;
}

void UGameOverlay::RegisterAllInformationCallbacks()
{
	const UPlayerAttributeSet* PlayerAttributes = GetPlayer()->GetPlayerAttributeSet();
	
	GetPlayer()->GetPlayerAbilitySystem()->GetGameplayAttributeValueChangeDelegate(PlayerAttributes->GetPlayerHealthAttribute())
	.AddUObject(this, &UGameOverlay::OnPlayerHealthChanged);

	GetPlayer()->GetPlayerAbilitySystem()->GetGameplayAttributeValueChangeDelegate(PlayerAttributes->GetPlayerArcanaAttribute())
	.AddUObject(this, &UGameOverlay::OnPlayerArcanaChanged);
}

void UGameOverlay::UnregisterAllInformationCallbacks()
{
	const UPlayerAttributeSet* PlayerAttributes = GetPlayer()->GetPlayerAttributeSet();

	GetPlayer()->GetPlayerAbilitySystem()->GetGameplayAttributeValueChangeDelegate(PlayerAttributes->GetPlayerHealthAttribute())
	.RemoveAll(this);

	GetPlayer()->GetPlayerAbilitySystem()->GetGameplayAttributeValueChangeDelegate(PlayerAttributes->GetPlayerArcanaAttribute())
	.RemoveAll(this);
}

void UGameOverlay::OnPlayerHealthChanged(const FOnAttributeChangeData& NewHealth)
{
	const float MaxHealth = GetPlayer()->GetPlayerAttributeSet()->GetPlayerMaxHealth();
	SetPlayerHealth(MaxHealth, NewHealth.NewValue);
}

void UGameOverlay::OnPlayerArcanaChanged(const FOnAttributeChangeData& NewArcana)
{
	const float MaxArcana = GetPlayer()->GetPlayerAttributeSet()->GetPlayerMaxArcana();
	SetPlayerArcana(MaxArcana, NewArcana.NewValue);
}

void UGameOverlay::SetPlayerHealth(const float MaxHealth, const float CurrentHealth) const
{
	PlayerHealthBar->SetPercent(CurrentHealth / MaxHealth);
	
	CurrentHealthText->SetText(FText::AsNumber(CurrentHealth));
	MaxHealthText->SetText(FText::AsNumber(MaxHealth));
}

void UGameOverlay::SetPlayerArcana(const float MaxArcana, const float CurrentArcana) const
{
	PlayerArcanaBar->SetPercent(CurrentArcana / MaxArcana);
}