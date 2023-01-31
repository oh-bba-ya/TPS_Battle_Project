// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetEnemy.h"
#include "Components/ProgressBar.h"

void UWidgetEnemy::PrintState(float current, float max)
{
	if (enemyHpBar == nullptr) return; //ÆÄ
	enemyHpBar->SetPercent(current / max);
}