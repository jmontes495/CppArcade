// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "GameFramework/Actor.h"
#include "TetrisPiece.generated.h"

UCLASS()
class SPACEINVADERS_API ATetrisPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisPiece();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<int32> HorizontalPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<int32> VerticalPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	ECellValue PieceType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<int32> GetRows();
	TArray<int32> GetColumns();
	ECellValue GetPieceType();
	TArray<int32> GetRotationHorizontals();
	TArray<int32> GetRotationVerticals();
	void Rotate();
};
