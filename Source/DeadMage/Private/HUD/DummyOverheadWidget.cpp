// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DummyOverheadWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// Interface
void UDummyOverheadWidget::SetHealthPercent_Implementation(float Health, float AppliedDamage)
{
	
	if (GetVisibility() != ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	
	UE_LOG(LogTemp, Error, TEXT("[%hs] NetRole: %i Health: %f AppliedDamage: %f"), __FUNCTION__, UGameplayStatics::GetPlayerController(this, 0)->GetLocalRole(), Health, AppliedDamage);
	SetHealthPercent(Health);
	ShowDamageNumber(AppliedDamage);
}

void UDummyOverheadWidget::SetHealthPercent(const float NewHealth) const
{
	HealthBar->SetPercent( FMath::Clamp(NewHealth, MIN_HEALTH , MAX_HEALTH) );
}

bool UDummyOverheadWidget::Initialize()
{
	SetVisibility(ESlateVisibility::Hidden);
	return Super::Initialize();
}

void UDummyOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}

void UDummyOverheadWidget::ShowDamageNumber(float AppliedDamage)
{
	if (!IsPlayingAnimation())
	{
		DamageAmount->SetText(FText::AsNumber(AppliedDamage));
		if (RefDamageAmountAnimation)
		{
			PlayAnimation(RefDamageAmountAnimation);
		}
	}
}
