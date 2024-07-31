// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DummyCharacter.h"

#include "AbilitySystem/AttributeSets/DummyAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/DummyWidgetInterface.h"

ADummyCharacter::ADummyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Attributes = CreateDefaultSubobject<UDummyAttributeSet>(TEXT("Attributes"));
	
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	if (OverheadWidget)
	{
		OverheadWidget->SetupAttachment(RootComponent);
	}

	if (AbilitySystem)
	{
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(Attributes->GetDummyHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	}
}

// Delegate callback function
void ADummyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue < 0) return;

	if (OverheadWidget && OverheadWidget->GetWidget() && OverheadWidget->GetWidget()->Implements<UDummyWidgetInterface>() )
	{
		float Health = Data.NewValue / Attributes->GetDummyMaxHealth();
		IDummyWidgetInterface::Execute_SetHealthPercent(OverheadWidget->GetWidget(), Health);
	}
}