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
	
	if (OverheadWidget && OverheadWidget->GetWidget() && OverheadWidget->GetWidget()->Implements<UDummyWidgetInterface>())
	{
		const float HealthPercent = Data.NewValue / Attributes->GetDummyMaxHealth();
		UE_LOG(LogTemp, Error, TEXT("[%hs] Role: %i Dummy old health %f , new health %f, MaxHealth %f"), __FUNCTION__, GetLocalRole(), Data.OldValue, Data.NewValue, Attributes->GetDummyMaxHealth());
		const float DamageNumber =  Data.OldValue - Data.NewValue;
		
		if (HealthPercent < 0) return;
		IDummyWidgetInterface::Execute_SetHealthPercent(OverheadWidget->GetWidget(), HealthPercent, DamageNumber);
	}
}