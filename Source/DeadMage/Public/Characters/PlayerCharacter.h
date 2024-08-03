// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Interfaces/PlayerCharacterInterface.h"
#include "PlayerCharacter.generated.h"

class UObjectPool;
class UPlayerAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

// To avoid the magic number
#define PRIORITY_0 0
#define FIRST_ATTACK 1

UCLASS()
class DEADMAGE_API APlayerCharacter : public ACharacterBase, public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UObjectPool> ObjectPoolComponent;
	
	// Gameplay Tags
	UPROPERTY(EditDefaultsOnly, Category = "Player|AbilityTags")
	FGameplayTag DashAbilityTag;

	UPROPERTY(EditDefaultsOnly, Category = "Player|AbilityTags")
	FGameplayTag AttackAbilityTag;
	// End of Gameplay Tags

	APlayerCharacter();
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ResetTheComboCycle();
	
	FORCEINLINE uint8 GetComboAttackNumber() const { return CurrentAttackNumber; }
	FORCEINLINE uint8 GetMaxComboAttack() const { return MaxComboAttack; }
	FORCEINLINE UPlayerAttributeSet* GetPlayerAttributeSet() const { return PlayerAttributes; }
	FORCEINLINE UAbilitySystemComponent* GetPlayerAbilitySystem() const { return AbilitySystem; }
	FORCEINLINE void IncreaseCurrentAttackNumber() { CurrentAttackNumber++; }

private:

	// Cache movement variables
	FVector2D MovementVector;

	FRotator Rotation;
	FRotator YawRotation;

	FVector ForwardDirection;
	FVector RightDirection;
	// End of cache movement variables

	// Combo system
	// Cache Attack cycle
	double LastAttackSecond { 0.0 };

	// Cache combo attack number
	uint8 CurrentAttackNumber { 0 };
	
	UPROPERTY(EditDefaultsOnly, Category = "Player|ComboSystem")
	uint8 MaxComboAttack { 3 };

	UPROPERTY(EditDefaultsOnly, Category = "Player|ComboSystem")
	float MaxDelayBetweenAttacks { 1.3 };
	// End of combo system

	// Refill arcana
	FTimerHandle RefillArcanaTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Player|GameplayEffects")
	float RefillDelay { 2.f };
	// End of refill arcana
	
	// Input actions and mapping
	UPROPERTY(EditDefaultsOnly, Category = "Player|InputActions")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Player|InputActions")
	TObjectPtr<UInputAction> IA_Movement;

	UPROPERTY(EditDefaultsOnly, Category = "Player|InputActions")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Player|InputActions")
	TObjectPtr<UInputAction> IA_Dash;
	// End of input actions and mapping

	// Player attributes
	UPROPERTY(Transient)
	TObjectPtr<UPlayerAttributeSet> PlayerAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Player|GameplayEffects")
	TSubclassOf<UGameplayEffect> ArcanaCoolDown;
	
	// Input callback functions
	void MovementAction(const FInputActionValue& Value);
	void AttackAction(const FInputActionValue& Value);
	void DashAction(const FInputActionValue& Value);
	// End of input callback functions

	// Add mapping context to enhanced input subsystem
	void SetInputMappingContext() const;

	// Interface
	virtual APlayerCharacter* GetPlayerCharacter_Implementation() override;

	// Delegate callback function
	void OnArcanaAttributeChanged(const FOnAttributeChangeData& Data);

	void RefillArcana();
};
