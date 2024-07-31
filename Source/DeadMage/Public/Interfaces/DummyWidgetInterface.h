// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DummyWidgetInterface.generated.h"

UINTERFACE()
class UDummyWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class DEADMAGE_API IDummyWidgetInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|UI")
	void SetHealthPercent(float& Health);
};
