// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacterFSM.h"
#include "BaseEnemyCharcter.h"
#include "BaseCharacter.h"
#include "BaseEnemyAnim.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>
#include "NavigationSystemTypes.h"
#include "NavigationSystem.h"

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

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass());
	target = Cast<ABaseCharacter>(actor);
	me = Cast<ABaseEnemyCharcter>(GetOwner());

	anim = Cast<UBaseEnemyAnim>(me->GetMesh()->GetAnimInstance());

	ai = Cast<AAIController>(me->GetController());
}

// Called every frame
void UBaseEnemyCharacterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	//me->AddMovementInput(dir.GetSafeNormal()*0.5f);
	/*ABaseEnemyCharcter* enemy = Cast<ABaseEnemyCharcter>(actor);
	FNavigationInvoker(enemy, 500.0f, 800.0f);*/
	//ai->MoveToLocation(destination);

	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;
	FAIMoveRequest req;

	req.SetAcceptanceRadius(3);
	req.SetGoalLocation(destination);
	ai->BuildPathfindingQuery(req, query);

	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(destination);
	}
	else
	{
		auto result = ai->MoveToLocation(randomPos);
		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
		}
	}

	if (dir.Size() < attackRange)
	{
		ai->StopMovement();
		mState = EEnemyState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime;
	}	
}

void UBaseEnemyCharacterFSM::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATTACK"));
		currentTime = 0;
		anim->bAttackPlay = true;
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		anim->animState = mState;
		
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
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
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);
	if (P.Z < -100.0f)
	{
		me->Destroy();
	}
}

void UBaseEnemyCharacterFSM::OnDamageProcess()
{
	enemyHP--;
	if (enemyHP > 0)
	{
		mState = EEnemyState::Damage;
		ai->StopMovement();
	}
	else 
	{
		mState = EEnemyState::Die;
		//me->GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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