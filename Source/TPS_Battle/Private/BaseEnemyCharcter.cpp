// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharcter.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseEnemyCharacterFSM.h"

// Sets default values
ABaseEnemyCharcter::ABaseEnemyCharcter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	//SetRootComponent(sceneComp);

	/*capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsuleComp"));
	capsuleComp->SetupAttachment(RootComponent);
	capsuleComp->SetCapsuleSize(50, 150);
	capsuleComp->SetRelativeLocation(FVector(0, 0, 0));	
	SetRootComponent(capsuleComp);*/

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/EnemyList/N01/Ch35_nonPBR.Ch35_nonPBR'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));		
		GetMesh()->SetupAttachment(RootComponent);		
	}
	fsm = CreateDefaultSubobject<UBaseEnemyCharacterFSM>(TEXT("FSM"));
	/*meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);*/

	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/BP_Enemy/ABP_BaseEnemyCharacter.ABP_BaseEnemyCharacter_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	pistolMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	pistolMeshComp->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	/*ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/Weapon/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A''"));
	if(tempGunMesh.Succeeded())
	{		
		pistolMeshComp->SetSkeletalMesh(tempGunMesh.Object);
		pistolMeshComp->SetRelativeLocation(FVector(-42, 7, 1));
		pistolMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}*/
}

// Called when the game starts or when spawned
void ABaseEnemyCharcter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemyCharcter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

