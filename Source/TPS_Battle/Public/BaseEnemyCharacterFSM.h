// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseEnemyCharacterFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack, 
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_BATTLE_API UBaseEnemyCharacterFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseEnemyCharacterFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	EEnemyState mState = EEnemyState::Idle;
			
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();	

	void OnDamageProcess(float a);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float idleDelayTime = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float currentTime = 0;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float dieDelayTime = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	class ABaseCharacter* target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	class ABaseEnemyCharcter* me;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float attackRange = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float attackDelayTime = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	int32 enemyHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	float dieSpeed = 50.0f;

	UPROPERTY()
	class UBaseEnemyAnim* anim;
	UPROPERTY()
	class AAIController* ai;

	FVector randomPos;
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* bloodEffect;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* EnemyMuzzleFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* enemyFireSound;	
};

