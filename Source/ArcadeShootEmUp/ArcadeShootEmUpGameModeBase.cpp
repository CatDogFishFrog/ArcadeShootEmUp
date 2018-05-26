// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcadeShootEmUpGameModeBase.h"

AArcadeShootEmUpGameModeBase::AArcadeShootEmUpGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
}
