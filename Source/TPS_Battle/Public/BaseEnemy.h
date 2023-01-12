// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TPS_BATTLE_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class UCapsuleComponent* capsuleComp;
	class UStaticMeshComponent* meshComp;

	int32 GetEnemyHP();
	void SetEnemyHP(int32 hp);

private:
	int32 enemyHP = 100;

};
