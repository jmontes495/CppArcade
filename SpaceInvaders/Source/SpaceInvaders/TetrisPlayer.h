// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "GameFramework/Pawn.h"
#include "TetrisPlayer.generated.h"

UCLASS()
class SPACEINVADERS_API ATetrisPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATetrisPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawning)
	TSubclassOf<class AGrid> GridBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class AGrid* Grid;
	bool bGameInProgress;

	void MoveLeft();
	void MoveRight();
	void SetDropDownSpeed();
	void SetNormalSpeed();
	void SavePiece();
	void Rotate();
	void PlayerPressedSpaceBar();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	ECellValue GetNextPieceType();

	UFUNCTION(BlueprintCallable)
	ECellValue GetSavedPieceType();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore();
};
