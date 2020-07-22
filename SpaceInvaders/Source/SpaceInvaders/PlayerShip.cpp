// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShip.h"
#include "Bullet.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Engine/World.h"

APlayerShip::APlayerShip()
{

	bUseControllerRotationYaw = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->InitBoxExtent(FVector(32.f));
	SetRootComponent(BoxComponent);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	Flipbook->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHorizontal", this, &APlayerShip::MoveHorizontal);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerShip::Shoot);
}

void APlayerShip::MoveHorizontal(float Value)
{
	if (Value == 0.0f)
		return;

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	CurrentDir = Direction * Value * MoveSpeed;
	FHitResult hitResult;
	AddActorLocalOffset(CurrentDir, true, &hitResult);

}

void APlayerShip::Shoot()
{
	if (BulletBP)
	{
		UWorld* World = GetWorld();
		FVector Location = GetActorLocation() + FVector(0.f, 0.f, 5.f);
		FActorSpawnParameters SpawnParams;
		if (World)
		{
			AActor* Actor = World->SpawnActor<AActor>(BulletBP, Location, FRotator(0.f), SpawnParams);
			ABullet* Bullet = Cast<ABullet>(Actor);			
		}
	}
}

void APlayerShip::IncreaseScore(int32 Value)
{
	Score += Value;
}

int32 APlayerShip::GetPlayerScore()
{
	return Score;
}


void APlayerShip::HitByProjectile()
{
	Destroy();
}