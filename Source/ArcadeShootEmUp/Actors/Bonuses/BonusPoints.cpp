// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeShootEmUpGameModeBase.h" 


void ABonusPoints::BonusCollected_Implementation()
{
	AArcadeShootEmUpGameModeBase* Gamemode = Cast<AArcadeShootEmUpGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(Points);

	Super::BonusCollected_Implementation();
}