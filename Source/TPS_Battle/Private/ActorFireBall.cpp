// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorFireBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AActorFireBall::AActorFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(sphereComp);

	sphereComp->SetSphereRadius(52);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));

	movementComp->SetUpdatedComponent(sphereComp);
	movementComp->InitialSpeed = 5000;
	movementComp->MaxSpeed = 5000;
	movementComp->bShouldBounce = false;

}

// Called when the game starts or when spawned
void AActorFireBall::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AActorFireBall::OnFireBallOverlap);
	
	player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AActorFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorFireBall::OnFireBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<ABaseCharacter>(OtherActor);
	if (player != nullptr) {
		player->OnHitEvent(Damage);
		player->OnCameraShake();
	}

	if (ExplosionImpact) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionImpact, GetActorLocation(), GetActorRotation());
	}

	Destroy();

}

void AActorFireBall::Splash()
{
	float dist = GetDistanceTo(player);
	if (dist <= ExplosionRange) {
		player->OnCameraShake();
	}

}

