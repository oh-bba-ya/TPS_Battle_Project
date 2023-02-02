// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossEnemyFSM.h"
#include "BossEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UBossEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimProperty)
		EBossState animState;

	
};
