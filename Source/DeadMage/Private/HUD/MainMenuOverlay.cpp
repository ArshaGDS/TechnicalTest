// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuOverlay.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenuOverlay::Initialize()
{
	Super::Initialize();
	
	ShowMouseCursor();
	InitializeEvents();
	
	return true;
}

void UMainMenuOverlay::ShowMouseCursor()
{
	if (GetWorld())
	{
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void UMainMenuOverlay::InitializeEvents()
{
	PlayButton->OnClicked.AddDynamic(this, &ThisClass::PlayButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
	
	PlayButton->OnHovered.AddDynamic(this, &ThisClass::PlayButtonHovered);
	PlayButton->OnUnhovered.AddDynamic(this, &ThisClass::PlayButtonUnHovered);

	QuitButton->OnHovered.AddDynamic(this, &ThisClass::QuitButtonHovered);
	QuitButton->OnUnhovered.AddDynamic(this, &ThisClass::QuitButtonUnHovered);

	PublisherButton->OnClicked.AddDynamic(this, &ThisClass::PublisherButtonClicked);
	DeadMageButton->OnClicked.AddDynamic(this, &ThisClass::DeadMageButtonClicked);
	DiscordButton->OnClicked.AddDynamic(this, &ThisClass::DiscordButtonClicked);
	SteamButton->OnClicked.AddDynamic(this, &ThisClass::SteamButtonClicked);
}

void UMainMenuOverlay::OpenWebsite(const TCHAR* Link)
{
	FPlatformProcess::LaunchURL(Link, NULL, NULL);
}

void UMainMenuOverlay::PlayButtonClicked()
{
	if (GetWorld())
	{
		UGameplayStatics::OpenLevel(this, TEXT("Arena_Map"), true);
	}
}

void UMainMenuOverlay::QuitButtonClicked()
{
	// Quit the game
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller && GetWorld())
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
	}
}

void UMainMenuOverlay::PlayButtonHovered()
{
	PlayButton->SetColorAndOpacity(SelectedTextColor);
	QuitButton->SetColorAndOpacity(DefaultTextColor);

	if (!MenuArrow->IsVisible())
		MenuArrow->SetVisibility(ESlateVisibility::Visible);
	
	MenuArrow->SetRenderTranslation(FVector2D());
}

void UMainMenuOverlay::PlayButtonUnHovered()
{
	PlayButton->SetColorAndOpacity(DefaultTextColor);
}

void UMainMenuOverlay::QuitButtonHovered()
{
	QuitButton->SetColorAndOpacity(SelectedTextColor);
	PlayButton->SetColorAndOpacity(DefaultTextColor);

	if (!MenuArrow->IsVisible())
		MenuArrow->SetVisibility(ESlateVisibility::Visible);

	MenuArrow->SetRenderTranslation(FVector2D(0, ArrowYOffset));
}

void UMainMenuOverlay::QuitButtonUnHovered()
{
	QuitButton->SetColorAndOpacity(DefaultTextColor);
}

void UMainMenuOverlay::PublisherButtonClicked()
{
	OpenWebsite(TEXT("https://www.humblegames.com/"));
}

void UMainMenuOverlay::DeadMageButtonClicked()
{
	OpenWebsite(TEXT("https://deadmage.com/"));
}

void UMainMenuOverlay::DiscordButtonClicked()
{
	OpenWebsite(TEXT("https://discord.com/"));
}

void UMainMenuOverlay::SteamButtonClicked()
{
	OpenWebsite(TEXT("https://store.steampowered.com/app/2193540/Wizard_of_Legend_2/"));
}

