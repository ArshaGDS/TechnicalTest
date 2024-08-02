// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FireballInterface.generated.h"

UINTERFACE()
class UFireballInterface : public UInterface
{
	GENERATED_BODY()
};

class DEADMAGE_API IFireballInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetFireballAttackState(bool IsFinisher);
};
