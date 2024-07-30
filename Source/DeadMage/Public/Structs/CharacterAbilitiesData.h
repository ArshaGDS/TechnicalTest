#pragma once

#include "CoreMinimal.h"
#include "CharacterAbilitiesData.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FCharacterAbilitiesData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};
