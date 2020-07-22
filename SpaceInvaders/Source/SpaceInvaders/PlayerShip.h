// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

UCLASS()
class SPACEINVADERS_API APlayerShip : public APawn
{
	GENERATED_BODY()

private:

	int32 Score;
	bool pIsMoving;
	FVector CurrentDir;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	APlayerShip();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawning)
	TSubclassOf<class AActor> BulletBP;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void MoveHorizontal(float Value);
	void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	void IncreaseScore(int32 Value);

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore();

	void HitByProjectile();

};
