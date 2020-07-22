// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisPlayer.h"
#include "Grid.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ATetrisPlayer::ATetrisPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATetrisPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GridBP)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;
		if (World)
		{
			AActor* Actor = World->SpawnActor<AGrid>(GridBP, GetActorLocation(), FRotator(0.f), SpawnParams);
			Grid = Cast<AGrid>(Actor);
		}
	}
}

// Called every frame
void ATetrisPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATetrisPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Left", IE_Released, this, &ATetrisPlayer::MoveLeft);
	PlayerInputComponent->BindAction("Right", IE_Released, this, &ATetrisPlayer::MoveRight);
	PlayerInputComponent->BindAction("Rotate", IE_Released, this, &ATetrisPlayer::Rotate);
	PlayerInputComponent->BindAction("DropDown", IE_Pressed, this, &ATetrisPlayer::SetDropDownSpeed);
	PlayerInputComponent->BindAction("SpaceBar", IE_Pressed, this, &ATetrisPlayer::PlayerPressedSpaceBar);
	PlayerInputComponent->BindAction("DropDown", IE_Released, this, &ATetrisPlayer::SetNormalSpeed);
	PlayerInputComponent->BindAction("SavePiece", IE_Released, this, &ATetrisPlayer::SavePiece);

}

void ATetrisPlayer::MoveLeft()
{
	if (Grid)
	{
		Grid->TryToMovePiece(-1.f);
	}
}

void ATetrisPlayer::MoveRight()
{
	if (Grid)
	{
		Grid->TryToMovePiece(1.f);
	}
}

void ATetrisPlayer::Rotate()
{
	if (Grid)
	{
		Grid->TryToRotatePiece();
	}
}

void ATetrisPlayer::SetNormalSpeed()
{
	if (Grid)
	{
		Grid->SetNormalSpeed();
	}
}

void ATetrisPlayer::SetDropDownSpeed()
{
	if (Grid)
	{
		Grid->SetDropDownSpeed();
	}
}

void ATetrisPlayer::SavePiece()
{
	if (Grid)
	{
		Grid->SavePiece();
	}
}

ECellValue ATetrisPlayer::GetNextPieceType()
{
	if (Grid)
	{
		return Grid->GetNextPieceType();
	}
	return ECellValue::ECV_Empty;
}

ECellValue ATetrisPlayer::GetSavedPieceType()
{
	if (Grid)
	{
		return Grid->GetSavedPieceType();
	}
	return ECellValue::ECV_Empty;
}

int32 ATetrisPlayer::GetPlayerScore()
{
	if (Grid)
	{
		return Grid->GetPlayerScore();
	}
	return 0;
}

void ATetrisPlayer::PlayerPressedSpaceBar()
{
	if (Grid)
	{
		if (Grid->IsGameInProgress())
		{
			Grid->DropPieceDown();
		}
		else
		{
			Grid->BeginTetrisMatch();
		}
	}
}


