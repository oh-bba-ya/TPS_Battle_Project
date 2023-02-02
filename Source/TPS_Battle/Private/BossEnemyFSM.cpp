// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyFSM.h"
#include "BaseCharacter.h"
#include "EnemyBoss.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossEnemyAnim.h"

// Sets default values for this component's properties
UBossEnemyFSM::UBossEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass());
	target = Cast<ABaseCharacter>(actor);
	me = Cast<AEnemyBoss>(GetOwner());

	bossState = EBossState::IDLE;

	anim = Cast<UBossEnemyAnim>(me->GetMesh()->GetAnimInstance());
	
}


// Called every frame
void UBossEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (bossState) {
		case EBossState::IDLE:
			IdleState();
			break;
		case EBossState::MOVE:
			MoveState();
			break;
		case EBossState::ATTACK:
			AttackState();
			break;
		case EBossState::DAMAGE:
			DamageState();
			break;
		case EBossState::DIE:
			DieState();
			break;
		default:
			break;
	}
}

void UBossEnemyFSM::IdleState()
{
	UE_LOG(LogTemp, Warning, TEXT("Idle"));
	if (GetDistanceToTarget(MoveRange)) {
		bossState = EBossState::MOVE;
	}
	else {
		bossState = EBossState::ATTACK;
	}
}

void UBossEnemyFSM::MoveState()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Move"));
	me->LookPlayer(GetWorld()->GetDeltaSeconds(), false);
	FVector dir = me->GetActorForwardVector();
	me->AddMovementInput(dir.GetSafeNormal());
	currentTime += GetWorld()->DeltaTimeSeconds;
	FVector distance = target->GetActorLocation() - me->GetActorLocation();

	if (distance.Size() > MoveRange) {
		anim->animState = EBossState::ATTACK;
		bossState = EBossState::ATTACK;
	}

}

void UBossEnemyFSM::AttackState()
{
	me->GetCharacterMovement()->StopMovementImmediately();
	me->LookPlayer(GetWorld()->GetDeltaSeconds());
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime >= attackDelayTime) {
		currentTime = 0;
		me->FireBall();
	}

	if (GetDistanceToTarget(MoveRange)) {
		anim->animState = EBossState::MOVE;
		bossState = EBossState::MOVE;
	}
}

void UBossEnemyFSM::DamageState()
{
}

void UBossEnemyFSM::DieState()
{
}

bool UBossEnemyFSM::GetDistanceToTarget(float length)
{
	const FVector destination = target->GetActorLocation();
	double dist = FVector::Dist(me->GetActorLocation(), destination);

	if (length >= dist) {
		return true;
	}

	return false;
}

