// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UENUM(BlueprintType)
enum class ECellValue : uint8
{
	ECV_Empty UMETA(DisplayName = "Empty"),
	ECV_Red UMETA(DisplayName = "Red"),
	ECV_Orange UMETA(DisplayName = "Orange"),
	ECV_Yellow UMETA(DisplayName = "Yellow"),
	ECV_Green UMETA(DisplayName = "Green"),
	ECV_Cyan UMETA(DisplayName = "Cyan"),
	ECV_Blue UMETA(DisplayName = "Blue"),
	ECV_Purple UMETA(DisplayName = "Purple"),

	ECV_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class SPACEINVADERS_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

private:
	ECellValue CellValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeColor(ECellValue newColor);

	UFUNCTION(BlueprintCallable)
	ECellValue GetCurrentCellValue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChangeSprite();
};
