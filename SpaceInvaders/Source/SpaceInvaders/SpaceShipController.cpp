// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShipController.h"
#include "Blueprint/UserWidget.h"

void ASpaceShipController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		HUDOverlay->AddToViewport();
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	}

	if (GameOverScreenAsset)
	{
		GameOverScreen = CreateWidget<UUserWidget>(this, GameOverScreenAsset);
		GameOverScreen->AddToViewport();
		GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASpaceShipController::ShowGameOver()
{
	if (GameOverScreen)
	{
		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

