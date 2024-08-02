// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DummyCharacter.h"

#include "AbilitySystem/AttributeSets/DummyAttributeSet.h"
#include "Components/CapsuleComponent.h"
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
		AbilitySystem->ReplicationMode = EGameplayEffectReplicationMode::Minimal;
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(Attributes->GetDummyHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	}
}

// Delegate callback function
void ADummyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue < 0)
	{
		DisableDummy();
		return;
	}
	
	if (OverheadWidget && OverheadWidget->GetWidget() && OverheadWidget->GetWidget()->Implements<UDummyWidgetInterface>())
	{
		const float HealthPercent = Data.NewValue / Attributes->GetDummyMaxHealth();
		const float DamageNumber =  Data.OldValue - Data.NewValue;
		
		IDummyWidgetInterface::Execute_SetHealthPercent(OverheadWidget->GetWidget(), HealthPercent, DamageNumber);
	}
}

void ADummyCharacter::DisableDummy()
{
	SetActorHiddenInGame(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(Attributes->GetDummyHealthAttribute())
	.RemoveAll(this);
}