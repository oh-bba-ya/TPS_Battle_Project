// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestEnemy.h"
#include "Components/SphereComponent.h"
#include "BaseCharacter.h"

// Sets default values
ATestEnemy::ATestEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestEnemy::BeginPlay()
{
	Super::BeginPlay();

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATestEnemy::OnSphereOverlap);
	
}

// Called every frame
void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestEnemy::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);
	if (player != nullptr) {
		player->OnHitEvent();
		UE_LOG(LogTemp, Warning, TEXT("Hit!!"));
	}
}

void ATestEnemy::DestroySelf()
{
	UE_LOG(LogTemp, Warning, TEXT("Call Destroy"));
}

