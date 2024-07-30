// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DummyOverheadWidget.h"

#include "Components/ProgressBar.h"

void UDummyOverheadWidget::SetHealthPercent(const float& NewHealth) const
{
	Healthbar->SetPercent( FMath::Clamp(NewHealth, MIN_HEALTH , MAX_HEALTH) );
}

// Interface
void UDummyOverheadWidget::SetHealthPercent_Implementation(float& Health)
{
	if (GetVisibility() != ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	
	SetHealthPercent(Health);
}

void UDummyOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
