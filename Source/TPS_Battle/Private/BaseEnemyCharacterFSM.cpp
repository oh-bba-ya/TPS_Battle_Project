// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacterFSM.h"
#include "BaseEnemyCharcter.h"
#include "BaseCharacter.h"
#include "BaseEnemyAnim.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>
#include "NavigationSystemTypes.h"
#include <NavigationSystem.h>
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/World.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WidgetPlayer.h"


// Sets default values for this component's properties
UBaseEnemyCharacterFSM::UBaseEnemyCharacterFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseEnemyCharacterFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	target = Cast<ABaseCharacter>(actor);
	me = Cast<ABaseEnemyCharcter>(GetOwner());
	anim = Cast<UBaseEnemyAnim>(me->GetMesh()->GetAnimInstance());
	ai = Cast<AAIController>(me->GetController());
}

// Called every frame
void UBaseEnemyCharacterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("FSM"));
	switch (mState)
	{
		case EEnemyState::Idle:
			IdleState();
			break;
		case EEnemyState::Move:
			MoveState();
			break;
		case EEnemyState::Attack:
			AttackState();
			break;
		case EEnemyState::Damage:
			DamageState();
			break;
		case EEnemyState::Die:
			DieState();
			break;	
	}
}

void UBaseEnemyCharacterFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		currentTime = 0;
		anim->animState = mState;
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
	}
}

void UBaseEnemyCharacterFSM::MoveState()
{	
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;
	FAIMoveRequest req;

	req.SetAcceptanceRadius(50);
	req.SetGoalLocation(destination);
	ai->BuildPathfindingQuery(req, query);

	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(destination);
		me->GetCharacterMovement()->MaxWalkSpeed = 300;
	}
	else
	{
		auto result = ai->MoveToLocation(randomPos);
		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			me->GetCharacterMovement()->MaxWalkSpeed = 150;
			GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
		}
	}

	if (dir.Size() < attackRange)
	{
		ai->StopMovement();
		mState = EEnemyState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = 0;
	}	
}

void UBaseEnemyCharacterFSM::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime)
	{
		currentTime = 0;
		anim->bAttackPlay = true;		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnemyMuzzleFactory, me->muzzleBox->GetComponentTransform());
		target->OnHitEvent(20);	
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		anim->animState = mState;		
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);				
	}
	else
	{
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(me->GetActorLocation(), PlayerLoc);
		me->SetActorRotation(PlayerRot);	
	}
}

void UBaseEnemyCharacterFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;	
	if (currentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
}

void UBaseEnemyCharacterFSM::DieState()
{	
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > dieDelayTime)
	{
		target->widgetPlayer->AddScore(1);
		me->Destroy();
	}
}

void UBaseEnemyCharacterFSM::OnDamageProcess(float a)
{
	me->enemyCurHP = me->enemyCurHP - a;
	const float randomRot = FMath::FRandRange(0.0f, 360.0f);
	FRotator Rot = me->GetActorRotation() * randomRot*0.001f;		
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), bloodEffect, me->GetActorLocation(), Rot, FVector(0.03));

	if (me->enemyCurHP > 0)
	{
		mState = EEnemyState::Damage;
		ai->StopMovement();
	}
	else if(me->enemyCurHP <=0)
	{
		mState = EEnemyState::Die;		
	}
	anim->animState = mState;
}

bool UBaseEnemyCharacterFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;
}