#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimData.generated.h"

class UBlendSpace1D;

USTRUCT(BlueprintType)
struct FCharacterAnimData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBlendSpace1D> MovementBlendSpace;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> IdleAnimationAsset;
};
