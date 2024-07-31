// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CharacterAnimInstance.h"

#include "Characters/PlayerCharacter.h"
#include "DataAssets/CharacterAnimDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerCharacterInterface.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (IsValid(TryGetPawnOwner()) && TryGetPawnOwner()->Implements<UPlayerCharacterInterface>())
	{
		PlayerCharacter = IPlayerCharacterInterface::Execute_GetPlayerCharacter(TryGetPawnOwner());
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsPlayerCharacterValid()) return;
	
	bIsAccelerating = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}

bool UCharacterAnimInstance::IsPlayerCharacterValid()
{
	if (PlayerCharacter == nullptr)
	{
		if (IsValid(TryGetPawnOwner()) && TryGetPawnOwner()->Implements<UPlayerCharacterInterface>())
		{
			PlayerCharacter = IPlayerCharacterInterface::Execute_GetPlayerCharacter(TryGetPawnOwner());
		}
	}

	return IsValid(PlayerCharacter);
}

UBlendSpace1D* UCharacterAnimInstance::GetLocomotionBlendSpace() const
{
	if (IsValid(CharacterAnimDataAsset))
	{
		return CharacterAnimDataAsset->CharacterAnimationData.MovementBlendSpace;
	}
	
	return nullptr;
}

UAnimSequenceBase* UCharacterAnimInstance::GetIdleAnimation() const
{
	if (IsValid(CharacterAnimDataAsset))
	{
		return CharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset;
	}

	return nullptr;
}