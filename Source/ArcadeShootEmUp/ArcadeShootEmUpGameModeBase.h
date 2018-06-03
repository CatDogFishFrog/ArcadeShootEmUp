// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "ArcadeShootEmUpGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class ARCADESHOOTEMUP_API AArcadeShootEmUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AArcadeShootEmUpGameModeBase();

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game") 
	void RecoverPawn();
	void RecoverPawn_Implementation();

	FTimerHandle RecoverTimer;
	bool IsGameOver;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnController* EnemySpawnController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
	UGameHealthComponent* HealthsComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPoints(int Points);

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int GamePoints;

};


