// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisPiece.h"

// Sets default values
ATetrisPiece::ATetrisPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATetrisPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATetrisPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<int32> ATetrisPiece::GetRows()
{
	return HorizontalPositions;
}

TArray<int32> ATetrisPiece::GetColumns()
{
	return VerticalPositions;
}

ECellValue ATetrisPiece::GetPieceType()
{
	return PieceType;
}

void ATetrisPiece::Rotate()
{
	TArray<int32> NewHorizontals;
	TArray<int32> NewVerticals;

	for (int32 i = 0; i < HorizontalPositions.Num(); i++)
	{
		NewHorizontals.Add(2 - VerticalPositions[i]);
		NewVerticals.Add(HorizontalPositions[i]);
	}

	HorizontalPositions = NewHorizontals;
	VerticalPositions = NewVerticals;
}

TArray<int32> ATetrisPiece::GetRotationHorizontals()
{
	TArray<int32> NewHorizontals;
	TArray<int32> NewVerticals;

	for (int32 i = 0; i < HorizontalPositions.Num(); i++)
	{
		NewHorizontals.Add(2 - VerticalPositions[i]);
		NewVerticals.Add(HorizontalPositions[i]);
	}

	return NewHorizontals;
}

TArray<int32> ATetrisPiece::GetRotationVerticals()
{
	TArray<int32> NewHorizontals;
	TArray<int32> NewVerticals;

	for (int32 i = 0; i < HorizontalPositions.Num(); i++)
	{
		NewHorizontals.Add(2 - VerticalPositions[i]);
		NewVerticals.Add(HorizontalPositions[i]);
	}

	return NewVerticals;
}

