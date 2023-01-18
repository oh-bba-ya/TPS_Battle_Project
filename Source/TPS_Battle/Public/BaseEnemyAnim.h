// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseEnemyCharacterFSM.h"
#include "BaseEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UBaseEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState animState;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FSM)
	bool bAttackPlay = false;
};
