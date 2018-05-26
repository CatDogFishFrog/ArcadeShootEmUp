// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnController.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Called when the game starts
void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	SpawnStage = FEnemySpawnInfo();
	SpawnStage.NumOfEnemies = 10;
	SpawnStage.SpawnDelay = 1.f;

	StartSpawnStage();
	
}

void UEnemySpawnController::StartSpawnStage()
{
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, true);
	
}

void UEnemySpawnController::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<APawn>(SpawnStage.EnemyClass,SpawnStage.SpawnTransform, SpawnParameters);
	UE_LOG(LogTemp, Log, TEXT("Spawn Enemy!!"));


	EnemiesSpawned++;
	if (EnemiesSpawned >= SpawnStage.NumOfEnemies) {
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
	}
}


