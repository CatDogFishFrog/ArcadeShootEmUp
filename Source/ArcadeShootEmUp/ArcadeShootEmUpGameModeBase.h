// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "ArcadeShootEmUpGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHOOTEMUP_API AArcadeShootEmUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AArcadeShootEmUpGameModeBase();

public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
		UEnemySpawnController* EnemySpawnController;
	
	
};
