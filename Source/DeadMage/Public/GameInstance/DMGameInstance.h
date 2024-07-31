// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEADMAGE_API UDMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
};
