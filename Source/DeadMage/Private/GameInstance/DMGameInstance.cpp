// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DMGameInstance.h"

#include "AbilitySystemGlobals.h"

void UDMGameInstance::Init()
{
	Super::Init();

	#if ENGINE_MAJOR_VERSION <= 5 && ENGINE_MINOR_VERSION < 3
	
	// Initialize GAS for engines older than 5.3 version
	UAbilitySystemGlobals::Get().InitGlobalData();
	
	#endif
}
