// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "DummyCharacter.generated.h"

class UWidgetComponent;
class UDummyAttributeSet;

UCLASS()
class DEADMAGE_API ADummyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	
	ADummyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> OverheadWidget;

private:

	// Player attributes
	UPROPERTY(Transient)
	TObjectPtr<UDummyAttributeSet> Attributes;
	
	// Delegate callback function
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
};
