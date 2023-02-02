// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossEnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8 {
	IDLE,
	MOVE,
	ATTACK,
	DAMAGE,
	DIE,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_BATTLE_API UBossEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
		EBossState bossState = EBossState::IDLE;

	void IdleState();

	void MoveState();

	void AttackState();

	void DamageState();

	void DieState();

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class ABaseCharacter* target;

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AEnemyBoss* me;

	float currentTime = 0;

	float MoveRange = 1500;


	float attackDelayTime = 3;

	bool GetDistanceToTarget(float length);

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class UBossEnemyAnim* anim;



};
