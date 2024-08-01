// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterBaseInterface.generated.h"

class ACharacterBase;

UINTERFACE()
class UCharacterBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEADMAGE_API ICharacterBaseInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Player")
	ACharacterBase* GetCharacterBase();
};
