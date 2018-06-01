// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcadeShootEmUpGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AArcadeShootEmUpGameModeBase::AArcadeShootEmUpGameModeBase()
	:
	PlayerRecoverTime(3)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeShootEmUpGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AArcadeShootEmUpGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeShootEmUpGameModeBase::ExplodePawn);
}

void AArcadeShootEmUpGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealthsComponent->ChangeHealths(-1);

	if(!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeShootEmUpGameModeBase::RecoverPawn_Implementation, PlayerRecoverTime, false);
}

void AArcadeShootEmUpGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AArcadeShootEmUpGameModeBase::EndGame()
{
	IsGameOver = true;

	EnemySpawnController->SetActive(false);

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!"));
}

 
