// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Alien.generated.h"

UCLASS()
class SPACEINVADERS_API AAlien : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldShoot;

private:
	TSubclassOf<class AActor> BulletBP;
	float ShootingChance;
	float ProjectileDelta;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ConfigShootValues(float Chance, float Delta, TSubclassOf<class AActor> Bullet);

	void GotKilled();

	void Shoot();

};
