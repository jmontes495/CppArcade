// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TetrisPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API ATetrisPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UUserWidget> HUDOverlayAsset;

	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UUserWidget> GameOverScreenAsset;

	UUserWidget* GameOverScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UUserWidget> IntroScreenAsset;

	UUserWidget* IntroScreen;

	void ShowGameOver();

	void ReturnToGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
