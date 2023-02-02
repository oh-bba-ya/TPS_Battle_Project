// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	sphereComp->SetupAttachment(rootComp);

	sphereComp->SetSphereRadius(150);

	niagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));

	niagaraComp->SetupAttachment(rootComp);

	niagaraComp->SetRelativeScale3D(FVector(3, 3, 3));

}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShield::ActiveShield(float delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Active Shield"));
	currentTime += 1;
	UE_LOG(LogTemp, Warning, TEXT("currentTime : %d"), currentTime);
}

void AShield::DeactiveShield()
{
	UE_LOG(LogTemp, Warning, TEXT("Deactive Shield"));
	currentTime = 0;
}

