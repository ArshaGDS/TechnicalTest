// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuOverlay.generated.h"

class UImage;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DEADMAGE_API UMainMenuOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> QuitText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> PlayButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> MenuArrow;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> PublisherButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> DeadMageButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> DiscordButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SteamButton;

	UPROPERTY(EditDefaultsOnly, Category = "MainMenu")
	FLinearColor SelectedTextColor;

	UPROPERTY(EditDefaultsOnly, Category = "MainMenu")
	FLinearColor DefaultTextColor;

protected:

	virtual bool Initialize() override;
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "MainMenu")
	float ArrowYOffset;
	
	void ShowMouseCursor();
	void InitializeEvents();
	void OpenWebsite(const TCHAR* Link);

	// UI callbacks
	UFUNCTION()
	void PlayButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void PlayButtonHovered();

	UFUNCTION()
	void PlayButtonUnHovered();

	UFUNCTION()
	void QuitButtonHovered();

	UFUNCTION()
	void QuitButtonUnHovered();

	UFUNCTION()
	void PublisherButtonClicked();

	UFUNCTION()
	void DeadMageButtonClicked();

	UFUNCTION()
	void DiscordButtonClicked();

	UFUNCTION()
	void SteamButtonClicked();
	// End of UI callbacks
};
