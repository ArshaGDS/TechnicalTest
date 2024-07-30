// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->bInheritYaw   = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll  = false;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->SetJumpAllowed(false);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bIgnoreBaseRotation = true;
	}

	PlayerAttributes = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetInputMappingContext();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Can't access to enhanced input component, so can't bind action mapping"), __FUNCTION__);
		return;
	}

	if (IA_Movement)
	{
		EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &ThisClass::MovementAction);
	}

	if (IA_Attack)
	{
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &ThisClass::AttackAction);
	}

	if (IA_Dash)
	{
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Started, this, &ThisClass::DashAction);
	}
}

void APlayerCharacter::MovementAction(const FInputActionValue& Value)
{
	if (Controller)
	{
		MovementVector = Value.Get<FVector2D>();
		
		Rotation = Controller->GetControlRotation();
		YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

		ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::AttackAction(const FInputActionValue& Value)
{
	SendGameplayEventToActor(this, AttackAbilityTag);
}

void APlayerCharacter::DashAction(const FInputActionValue& Value)
{
	SendGameplayEventToActor(this, DashAbilityTag);
}

void APlayerCharacter::SetInputMappingContext() const
{
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Can't access to player controller"), __FUNCTION__);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!EnhancedInputSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Can't access to enhanced input subsystem"), __FUNCTION__);
		return;
	}

	EnhancedInputSubsystem->AddMappingContext(PlayerMappingContext, PRIORITY_0);
}

// Interface
APlayerCharacter* APlayerCharacter::GetPlayerCharacter_Implementation()
{
	return this;
}


