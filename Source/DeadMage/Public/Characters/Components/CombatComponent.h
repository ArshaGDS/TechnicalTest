// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FStartedAttack, const uint8 AttackCount, const bool bIsFinisher);
DECLARE_MULTICAST_DELEGATE_TwoParams(FFinishedAttack, const uint8 AttackCount, const bool bIsFinisher);

class APlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADMAGE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatComponent();
	
	void Attack();

	FStartedAttack OnStartedAttack;
	FFinishedAttack OnFinishedAttack;

protected:

	// combat system
	// Cache Attack last attack time
	double LastAttackSecond { 0.0 };
	
	// Cache attack number
	UPROPERTY(Replicated)
	uint8 CurrentAttackNumber { 0 };
	
	UPROPERTY(EditDefaultsOnly, Category = "CombatSystem")
	uint8 MaxComboAttack { 3 };

	UPROPERTY(EditDefaultsOnly, Category = "CombatSystem")
	float MaxDelayBetweenAttacks { 1.3 };

	UPROPERTY(EditDefaultsOnly, Category = "CombatSystem")
	float FinisherDelay { 1.3f };
	// End of combat system

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacterPtr { nullptr };
	
	FTimerHandle FinisherTimerHandle;

	void FinisherFunction();
	void SpawnProjectile(const bool bIsFinisher);
	void ResetTheCombatCycle();
	
	APlayerCharacter* GetPlayer();

	FORCEINLINE void IncreaseCurrentAttackNumber() { CurrentAttackNumber++; };
	FORCEINLINE bool IsFinisherAttack() const { return  MaxComboAttack == CurrentAttackNumber; };
};
