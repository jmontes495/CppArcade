// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienManager.generated.h"

UCLASS()
class SPACEINVADERS_API AAlienManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 AliensPerRow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float DistanceBetweenAliens;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float DistanceBetweenRows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FVector AlienScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovingSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedDeltaOverRow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float HorizontalDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float VerticalDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<class AAlien>> AlienTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TSubclassOf<class AActor> BulletBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ProjectileDelta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootingChance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	float CurrentSpeed;
	FVector InitialPosition;
	FVector FinalPosition;
	FVector CurrentDirection;

	void GenerateAliens();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
