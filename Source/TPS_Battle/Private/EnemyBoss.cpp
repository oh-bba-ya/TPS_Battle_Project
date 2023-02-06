// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBoss.h"
#include "Components/CapsuleComponent.h"
#include "BossEnemyFSM.h"
#include "ActorFireBall.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyBoss::AEnemyBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FourEvilDragonsHP/Meshes/DragonTheUsurper/DragonTheUsurperSK.DragonTheUsurperSK'"));
	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -250), FRotator(0, -90, 0));
	}

	fsm = CreateDefaultSubobject<UBossEnemyFSM>(TEXT("FSM"));


}

// Called when the game starts or when spawned
void AEnemyBoss::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBoss::FireBall()
{
	if (fireBallFactory) {
		FVector tempLoc = GetActorLocation() + GetActorForwardVector() * 1;
		FTransform t = GetMesh()->GetSocketTransform(TEXT("FireBallSocket"));
		FVector temp = (player->GetActorLocation() - t.GetLocation());
		temp.Normalize();
		FRotator r = temp.Rotation();
		GetWorld()->SpawnActor<AActorFireBall>(fireBallFactory, t.GetLocation(), r);
	}

}

void AEnemyBoss::LookPlayer(float deltaTime, bool p)
{
	if (player != nullptr) {
		FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), player->GetActorLocation());

		if (p) {
			FRotator LookAtPlayer = FMath::RInterpTo(GetActorRotation(), LookRot, deltaTime, 2.0f);
			SetActorRotation(LookAtPlayer);
		}
		else {
			FRotator LookAtOpposite = FMath::RInterpTo(GetActorRotation(), LookRot * -1, deltaTime, 2.0f);
			SetActorRotation(FRotator(0,LookAtOpposite.Yaw,0));
		}
	}
}

