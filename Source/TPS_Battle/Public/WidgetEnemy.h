// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UWidgetEnemy : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings|HP", meta = (BindWidget))
	class UProgressBar* enemyHpBar;
	
	void PrintState(float current, float max);
};
