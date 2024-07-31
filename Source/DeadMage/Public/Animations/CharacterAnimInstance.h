// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/BlendSpace1D.h"
#include "CharacterAnimInstance.generated.h"

class UCharacterAnimDataAsset;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class DEADMAGE_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	TObjectPtr<const APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Character|Movement")
	bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|DataAssets")
	TObjectPtr<UCharacterAnimDataAsset> CharacterAnimDataAsset;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	bool IsPlayerCharacterValid();

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UBlendSpace1D* GetLocomotionBlendSpace() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UAnimSequenceBase* GetIdleAnimation() const;
};
