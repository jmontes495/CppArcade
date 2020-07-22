// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class SPACEINVADERS_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitResistance;

private:

	int32 HitsRemaining;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HitDefense();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DestroyedHalfPoint();
};
