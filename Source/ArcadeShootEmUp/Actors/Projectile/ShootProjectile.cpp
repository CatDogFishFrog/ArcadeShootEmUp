// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = Collision;

	//Collision->SetCollisionObjectType(ECC_WorldDynamic);
	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");

	
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		//UE_LOG(LogTemp, Log, TEXT("Owner!!"));
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);

}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Log, TEXT("Proj Overlapped!"));

	if (!GetOuter()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (!PawnOwner) return;
	AController* Instigator = PawnOwner->GetController();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigator, this, UDamageType::StaticClass());

	Destroy();
}

// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed*DeltaTime, 0.f, 0.f));

}

