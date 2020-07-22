// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class SPACEINVADERS_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float FallDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float FallDeltaOverProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DropDownMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ScorePerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<class ACell> CellType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<class ATetrisPiece>> Pieces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	class USoundCue* DownFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* MoveFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* RowFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* ComboFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* DeathFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* SaveFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* RotateFX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<TArray<class ACell*>> Cells;

	void GenerateCells();
	void CleanCells();

	bool ValidatePosition(int32 DeltaRow, int32 DeltaColumn);

	void SpawnNextPiece();

	void PaintPieceInCurrentPosition();
	void ClearCurrentPiece();
	bool PositionOccupiedByPiece(int32 TheRow, int32 TheColumn);
	void EvaluateCompleteLines();
	int32 GetIndexByType(ECellValue CellType);

	float FallElapsed;
	float CurrentDirection;
	float FallSpeed;
	float NormalSpeed;

	ATetrisPiece* CurrentPiece;
	int32 CurrentRow;
	int32 CurrentColumn;
	ECellValue NextPieceType;
	int32 NextPieceTypeIndex;
	ECellValue SavedPieceType;
	int32 SavedPieceTypeIndex;
	int32 PlayerScore;
	bool bIsEvaluating;
	bool bGameOver;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeginTetrisMatch();
	void MoveOnePositionDown();
	void TryToRotatePiece();
	void DropPieceDown();
	void SetDropDownSpeed();
	void SetNormalSpeed();
	void SavePiece();
	void TryToMovePiece(float Direction);
	ECellValue GetNextPieceType();
	ECellValue GetSavedPieceType();
	int32 GetPlayerScore();
	bool IsGameInProgress();
};
