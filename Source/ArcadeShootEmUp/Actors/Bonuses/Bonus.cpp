// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pawns/PlayerPawn.h"

// Sets default values
ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
 	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(50);
}


void ABonus::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Log, TEXT("Bonus overlap"));
	if(!OtherActor) return;
	if(!Cast<APlayerPawn>(OtherActor)) return;

	UE_LOG(LogTemp, Log, TEXT("Bonus CHAR overlap"));
	BonusCollected();

}


void ABonus::BonusCollected_Implementation()
{
	//if (CollectParticle)
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);

	Destroy();

}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -100.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}