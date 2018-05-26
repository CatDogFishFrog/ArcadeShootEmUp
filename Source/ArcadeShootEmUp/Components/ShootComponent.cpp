// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
	:
	ShootPediod(1.f)
{

	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
	
}

void UShootComponent::Shoot()
{
	UE_LOG(LogTemp, Log, TEXT("Shoot!!"));

	FActorSpawnParameters SpawnParameters;


	FVector SpawnLocation = GetOwner()->GetActorLocation();

	FRotator SpawnRotation = GetOwner()->GetActorRotation();
	//SpawnRotation.Add(0.f, 30.f, 0.f);

	GetWorld()->SpawnActor<AShootProjectile>(ProjetileClass, SpawnLocation, SpawnRotation, SpawnParameters);
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPediod, true, ShootPediod);
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}


