// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UAbilitySystemComponent;

UCLASS()
class DEADMAGE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();

private:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem; 
};
