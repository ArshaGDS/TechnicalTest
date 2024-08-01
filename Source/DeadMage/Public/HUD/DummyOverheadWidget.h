// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/DummyWidgetInterface.h"
#include "DummyOverheadWidget.generated.h"

class UTextBlock;
class UProgressBar;

#define MIN_HEALTH 0 
#define MAX_HEALTH 1 

UCLASS()
class DEADMAGE_API UDummyOverheadWidget : public UUserWidget, public IDummyWidgetInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UWidgetAnimation> RefDamageAmountAnimation;

	/*
	 *  Update healthbar
	 *  @param NewHealth: A float number between 0 and 1
	 */
	void SetHealthPercent(const float NewHealth) const;

	// Interface
	virtual void SetHealthPercent_Implementation(float Health, float AppliedDamage) override;

protected:
	
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	
	void ShowDamageNumber(float AppliedDamage);
};
