// Fill out your copyright notice in the Description page of Project Settings.

#include "AlienManager.h"
#include "Engine/World.h"
#include "Alien.h"

// Sets default values
AAlienManager::AAlienManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAlienManager::BeginPlay()
{
	Super::BeginPlay();
	CurrentSpeed = MovingSpeed;
	GenerateAliens();

	InitialPosition = GetActorLocation();
	FinalPosition = InitialPosition + FVector(HorizontalDistance, 0.f, 0.f);
	if (InitialPosition.X > FinalPosition.X)
		CurrentDirection = FVector(-1.f, 0.f, 0.f);
	else
		CurrentDirection = FVector(1.f, 0.f, 0.f);

}

// Called every frame
void AAlienManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult hitResult;
	AddActorLocalOffset(CurrentDirection * DeltaTime * MovingSpeed, true, &hitResult);
	
	float Distance = 0;
	if (CurrentDirection.X > 0)
		Distance = FinalPosition.X - GetActorLocation().X;
	else
		Distance = GetActorLocation().X - FinalPosition.X;

	if (Distance < 0.f)
	{
		CurrentSpeed += SpeedDeltaOverRow;
		SetActorLocation(FinalPosition + FVector(0.f, 0.f, -VerticalDistance));
		FinalPosition = InitialPosition + FVector(0.f, 0.f, -VerticalDistance);
		InitialPosition = GetActorLocation();
		
		if (InitialPosition.X > FinalPosition.X)
			CurrentDirection = FVector(-1.f, 0.f, 0.f);
		else
			CurrentDirection = FVector(1.f, 0.f, 0.f);
	}
}

void AAlienManager::GenerateAliens()
{
	for(int32 CurrentAlien = 0; CurrentAlien < AlienTypes.Num(); CurrentAlien++)
	{
		for (int32 index = 0; index < AliensPerRow; index++)
		{
			TSubclassOf<AAlien> Alien = AlienTypes[CurrentAlien];
			UWorld* World = GetWorld();
			FVector Location = GetActorLocation() + FVector(index*DistanceBetweenAliens, 0.f, -CurrentAlien*DistanceBetweenRows);
			FActorSpawnParameters SpawnParams;
			if (World)
			{
				AActor* Actor = World->SpawnActor<AActor>(Alien, Location, FRotator(0.f), SpawnParams);
				Actor->SetActorScale3D(AlienScale);
				Actor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
				AAlien* Alien = Cast<AAlien>(Actor);
				if (Alien)
					Alien->ConfigShootValues(ShootingChance, ProjectileDelta, BulletBP);
			}		
		}
	}
}

