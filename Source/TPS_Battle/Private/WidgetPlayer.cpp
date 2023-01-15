// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPlayer.h"
#include "Components/ProgressBar.h"

void UWidgetPlayer::PrintState(float current, float max, bool hp)
{
	if (hp) {
		hpBar->SetPercent(current / max);
	}
	else {
		mpBar->SetPercent(current / max );
	}
}
