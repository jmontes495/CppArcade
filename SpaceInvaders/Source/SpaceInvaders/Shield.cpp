// Fill out your copyright notice in the Description page of Project Settings.

#include "Shield.h"
#include "Components/BoxComponent.h"

// Sets default values
AShield::AShield()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	SetRootComponent(Collider);
}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	HitsRemaining = HitResistance;
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShield::HitDefense()
{
	HitsRemaining--;

	if (HitsRemaining <= 0)
	{
		Destroy();
		return;
	}

	if (HitsRemaining <= HitResistance / 2)
	{
		DestroyedHalfPoint();
	}
}

void AShield::DestroyedHalfPoint_Implementation()
{
	
}

