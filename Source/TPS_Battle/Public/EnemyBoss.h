// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBoss.generated.h"

UCLASS()
class TPS_BATTLE_API AEnemyBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(VisibleAnywhere, Category = BossSettings)
		class UBossEnemyFSM* fsm;

	UFUNCTION()
	void FireBall();


	UPROPERTY(EditAnywhere, Category = BossSettings)
		TSubclassOf<class AActorFireBall> fireBallFactory;

	UPROPERTY(VisibleAnywhere, Category = BossSettings)
		class ABaseCharacter* player;

	void LookPlayer(float deltaTime, bool p = true);

	UFUNCTION()
	void OnDamageEvnet(int32 damage);

	int32 BossHealth = 100;

	class ABattleGameModeBase* gm;


};
