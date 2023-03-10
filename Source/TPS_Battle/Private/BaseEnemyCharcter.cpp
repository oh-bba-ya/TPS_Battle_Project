// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharcter.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseEnemyCharacterFSM.h"
#include "WidgetEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseEnemyCharcter::ABaseEnemyCharcter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/EnemyList/N01/Ch35_nonPBR.Ch35_nonPBR'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetupAttachment(RootComponent);
	}
	enemyFSM = CreateDefaultSubobject<UBaseEnemyCharacterFSM>(TEXT("FSM"));

	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/BP_Enemy/ABP_BaseEnemyCharacter.ABP_BaseEnemyCharacter_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	pistolGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("pistolGunMeshComp"));
	pistolGunMeshComp->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/Weapon/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A'"));
	if (tempGunMesh.Succeeded())
	{
		pistolGunMeshComp->SetSkeletalMesh(tempGunMesh.Object);
		pistolGunMeshComp->SetRelativeLocation(FVector(-3, -5, 0));
		pistolGunMeshComp->SetRelativeRotation(FRotator(3, 90, 188));
	}
	muzzleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("muzzleBox"));
	muzzleBox->SetupAttachment(pistolGunMeshComp, TEXT("FirePosition"));

	hpWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("hpWidgetComp"));
	hpWidgetComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseEnemyCharcter::BeginPlay()
{
	Super::BeginPlay();

	widgetEnemy = Cast<UWidgetEnemy>(hpWidgetComp->GetWidget());	
}

// Called every frame
void ABaseEnemyCharcter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	widgetEnemy->PrintState(enemyCurHP, enemyMaxHP);
	FVector playloc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playloc);
	hpWidgetComp->SetWorldRotation(rot);
}

// Called to bind functionality to input
void ABaseEnemyCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemyCharcter::MySelfDestory()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Die"));	
	Destroy();
}

