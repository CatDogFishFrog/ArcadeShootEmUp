// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
APlayerPawn::APlayerPawn()
	:
	ToushMoveSensivity(1.2f), //Чуствительность тача
	MoveLimit(FVector2D(600.f, 500.f)) //Предел передвижения
	
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	 
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

} 

void APlayerPawn::PossessedBy(AController * NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

bool APlayerPawn::CanBeDamaged_Implementation()
{
	return bCanBeDamaged;
}


void APlayerPawn::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);
}

void APlayerPawn::RecoverPawn_Implementation()
{
	ShootComponent->StartShooting();

	SetActorEnableCollision(true);

	PawnMesh->SetMaterial(0, PawnMaterial);
}



// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PawnMaterial = PawnMesh->GetMaterial(0);
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!CanBeDamaged()) return 0.f;

	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);
	PawnDamaged.Broadcast();
	return Damage;
}

//Touch Controls
void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location) 
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	TouchDeltaMove *= ToushMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y); //Ограничитель передвижения по X
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X); //Ограничитель передвижения по Y

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("Touch Press : %s"), *TouchLocation.ToString());
	TouchLocation = FVector2D(Location.X, Location.Y);
}