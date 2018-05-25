// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.generated.h" 


UCLASS()
class ARCADESHOOTEMUP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void PossessedBy(AController* NewController) override;

	APlayerController* PlayerController;

private:

	FVector2D TouchLocation;

	bool Touching;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Controls)
		float ToushMoveSensivity;

};
