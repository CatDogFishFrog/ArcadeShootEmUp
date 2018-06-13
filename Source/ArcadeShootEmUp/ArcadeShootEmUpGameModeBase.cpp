// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcadeShootEmUpGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AArcadeShootEmUpGameModeBase::AArcadeShootEmUpGameModeBase() :
	PlayerRecoverTime(3),
	CurrentShootLevel(-1),
	IncreaseDifficultyPeriod(4.f)

{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeShootEmUpGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AArcadeShootEmUpGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeShootEmUpGameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &AArcadeShootEmUpGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
}

void AArcadeShootEmUpGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealthsComponent->ChangeHealths(-1);

	ChangeShootLevel(false);

	if (!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeShootEmUpGameModeBase::RecoverPawn, PlayerRecoverTime, false);
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

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!"));

	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AArcadeShootEmUpGameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95, 0.4);
	UE_LOG(LogTemp, Log, TEXT("Difficulty increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void AArcadeShootEmUpGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AArcadeShootEmUpGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
}

 
