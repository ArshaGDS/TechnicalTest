// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"

#include "Blueprint/UserWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	AddOverlay();	
}

void APlayerHUD::AddOverlay() const
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && LevelOverlayClass)
	{
		UUserWidget* CharacterOverlay = CreateWidget<UUserWidget>(PlayerController, LevelOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}
