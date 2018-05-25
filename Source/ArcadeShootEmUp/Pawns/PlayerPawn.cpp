// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(PawnCollision);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision);
	
	CamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamSpringArm"));
	CamSpringArm->SetupAttachment(RootComponent);
	 
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(CamSpringArm);

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
	
	bool Touch;
	float TouchX; float TouchY;
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, TouchX, TouchY, Touch);

	if (Touch) {
		FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - TouchX, TouchLocation.Y - TouchY);
		UE_LOG(LogTemp, Log, TEXT("Touching in %f-%f"), TouchLocation.X - TouchX, TouchLocation.Y - TouchY);

		AddActorLocalOffset(FVector(TouchDeltaMove.Y*-1.f, TouchDeltaMove.X, 0.f));

		TouchLocation = FVector2D(TouchX, TouchY);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Released, this, &APlayerPawn::OnTouchRelease);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("Touch Press : %s"), *TouchLocation.ToString());
	TouchLocation = FVector2D(Location);
	Touching = true;
}

void APlayerPawn::OnTouchRelease(ETouchIndex::Type FingerIndex, FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("Touch Release : %s"), *TouchLocation.ToString());
	Touching = false;
}

void APlayerPawn::PossessedBy(AController * NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}
