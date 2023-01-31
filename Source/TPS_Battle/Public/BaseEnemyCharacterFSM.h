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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;
			
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();	

	void OnDamageProcess(float a);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float idleDelayTime = 2;

	float currentTime = 0;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float dieDelayTime = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	class ABaseCharacter* target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	class ABaseEnemyCharcter* me;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float attackRange = 300.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float attackDelayTime = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	int32 enemyHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float dieSpeed = 50.0f;

	UPROPERTY()
	class UBaseEnemyAnim* anim;
	UPROPERTY()
	class AAIController* ai;

	FVector randomPos;
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* bloodEffect;
	//class UParticleSystem* bloodEffect;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunMesh)
	//class UBoxComponent* muzzleBox;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* EnemyMuzzleFactory;

	

};

