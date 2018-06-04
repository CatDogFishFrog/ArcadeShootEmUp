// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeShootEmUpGameModeBase.h" 

void ABonusShootLevelUp::BonusCollected_Implementation()
{
	AArcadeShootEmUpGameModeBase* Gamemode = Cast<AArcadeShootEmUpGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;

	Gamemode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();
}