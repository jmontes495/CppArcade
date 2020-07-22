// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceShipController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API ASpaceShipController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<UUserWidget> GameOverScreenAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		UUserWidget* GameOverScreen;

	void ShowGameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
