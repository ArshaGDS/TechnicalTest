// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/CharacterAbilitiesData.h"
#include "CharacterAbilitiesDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DEADMAGE_API UCharacterAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FCharacterAbilitiesData CharacterData;
};
