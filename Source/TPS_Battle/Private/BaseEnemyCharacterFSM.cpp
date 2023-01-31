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

	//auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass());
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
		//UE_LOG(LogTemp, Warning, TEXT("Idle"));
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
	//UE_LOG(LogTemp, Warning, TEXT("Move1"));
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;
	FAIMoveRequest req;

	req.SetAcceptanceRadius(50);
	req.SetGoalLocation(destination);
	ai->BuildPathfindingQuery(req, query);

	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		//FVector speed = destination * 0.1;
		ai->MoveToLocation(destination);
		//UE_LOG(LogTemp, Warning, TEXT("Move2 : go Target"));
		me->GetCharacterMovement()->MaxWalkSpeed = 300;
	}
	else
	{
		auto result = ai->MoveToLocation(randomPos);
		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			me->GetCharacterMovement()->MaxWalkSpeed = 150;
			GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
			//UE_LOG(LogTemp, Warning, TEXT("Move3 : go Random Loc"));
		}
	}

	if (dir.Size() < attackRange)
	{
		ai->StopMovement();
		mState = EEnemyState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime;
		UE_LOG(LogTemp, Warning, TEXT("Move4 : go Attack"));
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

		//muzzleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("muzzleBox"));
		//muzzleBox->SetupAttachment(me->pistolGunMeshComp, TEXT("FirePosition"));
		/*
		FTransform muzzlePos = Cast<ABaseEnemyCharcter>(GetComponentTransform()->muzzleBox);
		FTransform muzzlePos = Cast<ABaseEnemyCharcter>(me->muzzleBox);*/

		/*const USkeletalMeshSocket* MuzzleFlashSocket = me->pistolGunMeshComp->GetSocketByName(FName("FirePosition"));
		FTransform muzzleBox = GetSocketTransform(MuzzleFlashSocket);*/

		//auto muzzlePos = Cast<ABaseEnemyCharcter>(me->pistolGunMeshComp->GetComponentTransform());
		//auto muzzlePos = me->pistolGunMeshComp->GetComponentTransform();
		//auto muzzle = me->pistolGunMeshComp->GetSocketByName(FName("FirePosition"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnemyMuzzleFactory, me->muzzleBox->GetComponentTransform());
		target->OnHitEvent(20);
		
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		anim->animState = mState;		
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);		
		UE_LOG(LogTemp, Warning, TEXT("Go to Move"));
	}
	else
	{
		//FVector destination = target->GetActorLocation();
		//FVector dir = destination - me->GetActorLocation();
		//FRotator(dir);
		//me->SetActorRotation(dir);
		//me->AddActorWorldRotation(dir);
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(me->GetActorLocation(), PlayerLoc);
		//FRotator NewRot = FMath::RInterpTo(StaticMesh2->GetComponentRotation(), PlayerRot, GetWorld()->DeltaTimeSeconds, 2);
		//FRotator Newrot = (PlayerLoc - StaticMesh2->GetComponentLocation()).Rotation();
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
	target->widgetPlayer->AddScore(1);
	
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > dieDelayTime)
	{
		me->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Die"));		
	}
	/*
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateLambda([this]()->void
	{
		me->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Die"));
		target->widgetPlayer->AddScore(1);
	}), DelayTime, false);
	*/
	//me->GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//me->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//FVector P0 = me->GetActorLocation();
	//FVector vt = FVector::UpVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	//FVector P = P0 + vt;
	//me->SetActorLocation(P);
	//if (P.Z < -50.0f)
	//{
	//	me->Destroy();
	//}
}

void UBaseEnemyCharacterFSM::OnDamageProcess(float a)
{
	me->enemyCurHP = me->enemyCurHP - a;
	UE_LOG(LogTemp, Warning, TEXT("DamagePower : %d"), a);
	const float randomRot = FMath::FRandRange(1.0f, 180.0f);
	FRotator Rot = me->GetActorRotation()*randomRot;	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), bloodEffect, me->GetActorLocation(), Rot, FVector(0.03));
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), bloodEffect, me->GetActorLocation(), me->GetActorRotation(), FVector(0.03));
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bloodEffect, me->GetActorLocation(), me->GetActorRotation());
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