// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuOverlay.generated.h"

class UButton;
class UImage;
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
	TObjectPtr<UImage> PublisherIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> DeadMageIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> DiscordIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> SteamIcon;

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
	// End of UI callbacks
};
