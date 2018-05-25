// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerPawn::APlayerPawn()
	:
	ToushMoveSensivity(1.2) //Чуствительность тача
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	
	/*CamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamSpringArm"));
	CamSpringArm->SetupAttachment(RootComponent);*/
	 
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	//PawnCamera->SetupAttachment(CamSpringArm);

} 

void APlayerPawn::PossessedBy(AController * NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	 
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
	//InputComponent->BindTouch(IE_Released, this, &APlayerPawn::OnTouchRelease);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

//Touch Controls
void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location) 
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	TouchDeltaMove *= ToushMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -500.f, 500.f); //Ограничитель передвижения по X
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -600.f, 600.f); //Ограничитель передвижения по Y

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("Touch Press : %s"), *TouchLocation.ToString());
	TouchLocation = FVector2D(Location.X, Location.Y);
}


