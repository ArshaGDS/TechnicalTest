// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSets/DummyAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

class APlayerCharacter;
class UProgressBar;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class DEADMAGE_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerHealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PlayerArcanaBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentHealthText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHealthText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AttackIcon;

	void SetPlayerHealth(const float MaxHealth, const float CurrentHealth) const;
	void SetPlayerArcana(const float MaxArcana, const float CurrentArcana) const;

private:
	
	UPROPERTY()
	APlayerCharacter* CurrentPlayer { nullptr };

	APlayerCharacter*  GetPlayer();

	// Fill UI Text, Progressbar & etc
	void InitializeUIData();
	
	// Bind Healthbars, health number & etc delgates
	void RegisterAllInformationCallbacks();
	void UnregisterAllInformationCallbacks();

	// Delegate callbacks
	void OnPlayerHealthChanged(const FOnAttributeChangeData& NewHealth);
	void OnPlayerArcanaChanged(const FOnAttributeChangeData& NewArcana);
	// ~End of delegate callbacks

	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
};
