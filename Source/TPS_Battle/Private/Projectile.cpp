// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(10, 5, 5));
	boxComp->bHiddenInGame = false;
	boxComp->SetLineThickness(2.0f);

	// FName은 대소문자 구분 안함
	boxComp->SetCollisionProfileName(TEXT("BlockAll"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(boxComp);

	meshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));

	movementComp->SetUpdatedComponent(boxComp);
	movementComp->InitialSpeed = Speed;
	movementComp->MaxSpeed = Speed;
	movementComp->bShouldBounce = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBulletOverlap);

	DestoryTimeBullet();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AProjectile::DestoryBullet()
{
	Destroy();
}

void AProjectile::DestoryTimeBullet()
{
	FTimerHandle destoryTime;
	GetWorld()->GetTimerManager().SetTimer(destoryTime, this, &AProjectile::DestoryBullet, destroyBulletTime, false);
}

