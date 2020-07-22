// Fill out your copyright notice in the Description page of Project Settings.

#include "Alien.h"
#include "AlienBullet.h"
#include "Components/BoxComponent.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"

// Sets default values
AAlien::AAlien()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	SetRootComponent(Collider);

	Flipbook = CreateDefaultSubobject< UPaperFlipbookComponent>("Flipbook");
	Flipbook->SetupAttachment(RootComponent);
	Flipbook->SetRelativeLocation(FVector(0.f));
}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlien::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bShouldShoot)
		return;

	ProjectileDelta += DeltaTime;
	if (ProjectileDelta > 5.f)
	{
		float ShootingRand = FMath::FRandRange(0.f, 1.f);
		if (ShootingRand <= ShootingChance)
			Shoot();
		ProjectileDelta = 0;
	}

}

void AAlien::GotKilled()
{
	Destroy();
}

void AAlien::Shoot()
{
	if (BulletBP)
	{
		UWorld* World = GetWorld();
		FVector Location = GetActorLocation() + FVector(0.f, 0.f, 5.f);
		FActorSpawnParameters SpawnParams;
		if (World)
		{
			AActor* Actor = World->SpawnActor<AActor>(BulletBP, Location, FRotator(0.f), SpawnParams);
			AAlienBullet* Bullet = Cast<AAlienBullet>(Actor);
		}
	}
}

void AAlien::ConfigShootValues(float Chance, float Delta, TSubclassOf<class AActor> Bullet)
{
	BulletBP = Bullet;
	ShootingChance = Chance;
	ProjectileDelta = Delta;
}


