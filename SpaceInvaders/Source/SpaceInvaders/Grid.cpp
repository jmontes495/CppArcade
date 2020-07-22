// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"
#include "Cell.h"
#include "TetrisPiece.h"
#include "GameFramework/PlayerController.h"
#include "TetrisPlayerController.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	GenerateCells();
	bGameOver = true;	
}

void AGrid::BeginTetrisMatch()
{
	ATetrisPlayerController* MainController = Cast<ATetrisPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MainController)
	{
		MainController->ReturnToGame();
	}

	int32 RandomIndex = FMath::RandRange(0, 6);
	NextPieceType = Pieces[RandomIndex].GetDefaultObject()->GetPieceType();
	NextPieceTypeIndex = RandomIndex;

	CleanCells();
	SpawnNextPiece();

	SavedPieceType = ECellValue::ECV_Empty;
	FallSpeed = FallDelay;
	NormalSpeed = FallDelay;
	bIsEvaluating = false;
	bGameOver = false;
	PlayerScore = 0;
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (!CurrentPiece || bIsEvaluating || bGameOver)
		return;

	FallElapsed += DeltaTime;
	
	if (FallElapsed > FallSpeed)
	{
		FallElapsed = 0.f;
		if (ValidatePosition(CurrentRow + 1, CurrentColumn))
		{
			MoveOnePositionDown();
		}
		else
		{
			EvaluateCompleteLines();
		}
	}
}

void AGrid::GenerateCells()
{	
	for (int32 Row = 0; Row < Height; Row++)
	{
		TArray<ACell*> CurrentRow;
		
		for (int32 Column = 0; Column < Width; Column++)
		{
			UWorld* World = GetWorld();
			FVector Location = GetActorLocation() + FVector(Column*CellSize, 0.f, -Row * CellSize);
			FActorSpawnParameters SpawnParams;
			if (World)
			{
				AActor* Actor = World->SpawnActor<AActor>(CellType, Location, FRotator(0.f), SpawnParams);
				Actor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			
				ACell* NewCell = Cast<ACell>(Actor);
				CurrentRow.Add(NewCell);
			}
		}
		Cells.Add(CurrentRow);
	}
}

void AGrid::CleanCells()
{
	for (int32 Row = 0; Row < Height; Row++)
	{
		for (int32 Column = 0; Column < Width; Column++)
		{
			Cells[Row][Column]->ChangeColor(ECellValue::ECV_Empty);
		}
	}
}

void AGrid::SpawnNextPiece()
{
	CurrentRow = 2;
	CurrentColumn = 4;

	CurrentPiece = Pieces[NextPieceTypeIndex].GetDefaultObject();
	int32 RandomIndex = FMath::RandRange(0, 6);
	NextPieceType = Pieces[RandomIndex].GetDefaultObject()->GetPieceType();
	NextPieceTypeIndex = RandomIndex;
	
	TArray<int32> Rows = CurrentPiece->GetRows();
	TArray<int32> Columns = CurrentPiece->GetColumns();
	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		if (Cells[CurrentRow + Rows[Row]][CurrentColumn + Columns[Row]]->GetCurrentCellValue() != ECellValue::ECV_Empty)
		{
			ATetrisPlayerController* MainController = Cast<ATetrisPlayerController>(GetWorld()->GetFirstPlayerController());
			if (MainController)
			{
				MainController->ShowGameOver();
			}
			if (DeathFX)
			{
				UGameplayStatics::PlaySound2D(this, DeathFX);
			}
			bGameOver = true;
			return;
		}
	}
	
	PaintPieceInCurrentPosition();
}

void AGrid::MoveOnePositionDown()
{
	ClearCurrentPiece();
	CurrentRow++;
	PaintPieceInCurrentPosition();
	if (DownFX)
	{
		UGameplayStatics::PlaySound2D(this, DownFX);
	}
}

void AGrid::ClearCurrentPiece()
{
	TArray<int32> Rows = CurrentPiece->GetRows();
	TArray<int32> Columns = CurrentPiece->GetColumns();
	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		Cells[CurrentRow + Rows[Row]][CurrentColumn + Columns[Row]]->ChangeColor(ECellValue::ECV_Empty);
	}
}

void AGrid::PaintPieceInCurrentPosition()
{
	TArray<int32> Rows = CurrentPiece->GetRows();
	TArray<int32> Columns = CurrentPiece->GetColumns();
	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		Cells[CurrentRow + Rows[Row]][CurrentColumn + Columns[Row]]->ChangeColor(CurrentPiece->GetPieceType());
	}
}


bool AGrid::ValidatePosition(int32 NextRow, int32 NextColumn)
{
	TArray<int32> Rows = CurrentPiece->GetRows();
	TArray<int32> Columns = CurrentPiece->GetColumns();
	
	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		if (Rows[Row] + NextRow >= Height || Rows[Row] + NextRow < 0)
			return false;
		else if (Columns[Row] + NextColumn >= Width || Columns[Row] + NextColumn < 0)
			return false;
		else if (Cells[NextRow + Rows[Row]][NextColumn + Columns[Row]]->GetCurrentCellValue() != ECellValue::ECV_Empty && !PositionOccupiedByPiece(NextRow + Rows[Row], NextColumn + Columns[Row]))
			return false;
	}
	return true;
}

bool AGrid::PositionOccupiedByPiece(int32 TheRow, int32 TheColumn)
{
	TArray<int32> Rows = CurrentPiece->GetRows();
	TArray<int32> Columns = CurrentPiece->GetColumns();

	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		if (CurrentRow + Rows[Row] == TheRow && CurrentColumn + Columns[Row] == TheColumn)
			return true;
	}
	return false;
}

void AGrid::TryToMovePiece(float Direction)
{
	if (bIsEvaluating || bGameOver)
		return;

	if (Direction > 0.f || Direction < 0.f)
	{
		if (Direction > 0.f && ValidatePosition(CurrentRow, CurrentColumn + 1))
		{
			ClearCurrentPiece();
			CurrentColumn++;
			PaintPieceInCurrentPosition();
			if (MoveFX)
			{
				UGameplayStatics::PlaySound2D(this, MoveFX);
			}
		}
		else if (Direction < 0.f && ValidatePosition(CurrentRow, CurrentColumn - 1))
		{
			ClearCurrentPiece();
			CurrentColumn--;
			PaintPieceInCurrentPosition();
			if (MoveFX)
			{
				UGameplayStatics::PlaySound2D(this, MoveFX);
			}
		}
	}
}

void AGrid::TryToRotatePiece()
{
	if (bIsEvaluating || bGameOver)
		return;

	TArray<int32> Rows = CurrentPiece->GetRotationHorizontals();
	TArray<int32> Columns = CurrentPiece->GetRotationVerticals();

	for (int32 Row = 0; Row < Rows.Num(); Row++)
	{
		if (Rows[Row] + CurrentRow >= Height || Rows[Row] + CurrentRow < 0)
			return;
		else if (Columns[Row] + CurrentColumn >= Width || Columns[Row] + CurrentColumn < 0)
			return;
		else if (Cells[CurrentRow + Rows[Row]][CurrentColumn + Columns[Row]]->GetCurrentCellValue() != ECellValue::ECV_Empty && !PositionOccupiedByPiece(CurrentRow + Rows[Row], CurrentColumn + Columns[Row]))
			return;
	}

	if (RotateFX)
	{
		UGameplayStatics::PlaySound2D(this, RotateFX);
	}
	ClearCurrentPiece();
	CurrentPiece->Rotate();
	PaintPieceInCurrentPosition();
}

void AGrid::SetDropDownSpeed()
{
	FallSpeed = NormalSpeed * DropDownMultiplier;
}

void AGrid::SetNormalSpeed()
{
	FallSpeed = NormalSpeed;
}

void AGrid::SavePiece()
{
	if (bIsEvaluating || bGameOver)
		return;

	if (SavedPieceType == ECellValue::ECV_Empty)
	{
		if (NextPieceType == ECellValue::ECV_Empty)
		{
			int32 RandomIndex = FMath::RandRange(0, 6);
			SavedPieceType = Pieces[RandomIndex].GetDefaultObject()->GetPieceType();
			SavedPieceTypeIndex = RandomIndex;
		}
		else
		{
			SavedPieceType = NextPieceType;
			SavedPieceTypeIndex = NextPieceTypeIndex;
			int32 RandomIndex = FMath::RandRange(0, 6);
			NextPieceType = Pieces[RandomIndex].GetDefaultObject()->GetPieceType();
			NextPieceTypeIndex = RandomIndex;
		}
	}

	ECellValue SwitchPiece = SavedPieceType;
	int32 SwitchPieceIndex = SavedPieceTypeIndex;
	
	ClearCurrentPiece();
	
	SavedPieceType = CurrentPiece->GetPieceType();
	SavedPieceTypeIndex = GetIndexByType(SavedPieceType);
	CurrentPiece = Pieces[SwitchPieceIndex].GetDefaultObject();
	PaintPieceInCurrentPosition();

	if (SaveFX)
	{
		UGameplayStatics::PlaySound2D(this, SaveFX);
	}
}

int32 AGrid::GetIndexByType(ECellValue CellType)
{
	for (int32 Index = 0; Index < Pieces.Num(); Index++)
	{
		if (Pieces[Index].GetDefaultObject()->GetPieceType() == CellType)
			return Index;
	}
	return 0;
}

void AGrid::EvaluateCompleteLines()
{
	bIsEvaluating = true;
	int32 RowsCompleted = 0;

	int32 Row = Height - 1;
	while (Row >= 0)
	{
		int32 FullCells = 0;
		for (int32 Column = 0; Column < Width; Column++)
		{
			if (Cells[Row][Column]->GetCurrentCellValue() != ECellValue::ECV_Empty)
				FullCells++;
		}

		if (FullCells == Width)
		{
			RowsCompleted++;

			NormalSpeed -= FallDeltaOverProgress;
			if (NormalSpeed < 0.f)
				NormalSpeed = 0.f;
			
			for (int32 MovingRow = Row; MovingRow > 0; MovingRow--)
			{
				for (int32 MovingColumn = 0; MovingColumn < Width; MovingColumn++)
				{
					Cells[MovingRow][MovingColumn]->ChangeColor(Cells[MovingRow - 1][MovingColumn]->GetCurrentCellValue());
				}				
			}
		}
		else
			Row--;
	}

	if (RowsCompleted == 1)
	{
		if (RowFX)
		{
			UGameplayStatics::PlaySound2D(this, RowFX);
		}
	}
	else if (RowsCompleted > 1)
	{
		if (ComboFX)
		{
			UGameplayStatics::PlaySound2D(this, ComboFX);
		}
	}
	for (int32 i = 0; i < RowsCompleted; i++)
	{
		PlayerScore += (i + 1) * ScorePerRow;
	}

	SpawnNextPiece();
	bIsEvaluating = false;
}

ECellValue AGrid::GetNextPieceType()
{
	return NextPieceType;
}

ECellValue AGrid::GetSavedPieceType()
{
	return SavedPieceType;
}

int32 AGrid::GetPlayerScore()
{
	return PlayerScore;
}

bool AGrid::IsGameInProgress()
{
	return !bGameOver;
}

void AGrid::DropPieceDown()
{
	while (ValidatePosition(CurrentRow + 1, CurrentColumn))
	{
		ClearCurrentPiece();
		CurrentRow++;
		PaintPieceInCurrentPosition();
	}
	if (DownFX)
	{
		UGameplayStatics::PlaySound2D(this, DownFX);
	}
	EvaluateCompleteLines();
}
