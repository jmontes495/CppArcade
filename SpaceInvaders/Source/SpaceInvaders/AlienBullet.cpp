// Fill out your copyright notice in the Description page of Project Settings.

#include "AlienBullet.h"
#include "PlayerShip.h"
#include "Shield.h"
#include "Components/BoxComponent.h"
#include "Paper2D/Classes/PaperTileMapActor.h"

// Sets default values
AAlienBullet::AAlienBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->InitBoxExtent(FVector(5.f, 10.f, 10.f));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	bIsMoving = true;
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void AAlienBullet::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAlienBullet::OnBulletTouchedObject);

}

void AAlienBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		FVector Direction = FVector(0.f, 0.f, -1.f);

		FHitResult hitResult;
		AddActorLocalOffset(Direction * ProjectileSpeed * DeltaTime, true, &hitResult);
	}
}

void AAlienBullet::OnBulletTouchedObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		APaperTileMapActor* TileMap = Cast<APaperTileMapActor>(OtherActor);
		if (TileMap)
		{
			bIsMoving = false;
			Destroy();
			return;
		}

		APlayerShip* Player = Cast<APlayerShip>(OtherActor);
		if (Player)
		{
			Player->HitByProjectile();
			Destroy();
			return;
		}

		AShield* Shield = Cast<AShield>(OtherActor);
		if (Shield)
		{
			Shield->HitDefense();
			Destroy();
			return;
		}
	}
}

