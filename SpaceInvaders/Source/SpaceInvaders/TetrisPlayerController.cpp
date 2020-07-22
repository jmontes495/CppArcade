// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisPlayerController.h"
#include "Blueprint/UserWidget.h"

void ATetrisPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		HUDOverlay->AddToViewport();
		HUDOverlay->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameOverScreenAsset)
	{
		GameOverScreen = CreateWidget<UUserWidget>(this, GameOverScreenAsset);
		GameOverScreen->AddToViewport();
		GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	}

	if (IntroScreenAsset)
	{
		IntroScreen = CreateWidget<UUserWidget>(this, IntroScreenAsset);
		IntroScreen->AddToViewport();
		IntroScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATetrisPlayerController::ShowGameOver()
{
	if (GameOverScreen)
	{
		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATetrisPlayerController::ReturnToGame()
{
	if (HUDOverlay)
	{
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	}

	if (GameOverScreen)
	{
		GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	}

	if (IntroScreen && IntroScreen->GetVisibility() == ESlateVisibility::Visible)
	{
		IntroScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}