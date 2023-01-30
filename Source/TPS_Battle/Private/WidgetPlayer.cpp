// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPlayer.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetPlayer::PrintState(float current, float max, bool hp)
{
	if (hp) {
		hpBar->SetPercent(current / max);
	}
	else {
		mpBar->SetPercent(current / max );
	}
}

void UWidgetPlayer::AddScore(int32 point)
{
	currentScore += point;
	if (Score) {
		Score->SetText(FText::AsNumber(currentScore));
		// scoreAnim 애니메이션을 실행한다.
		PlayAnimation(scoreAnim, 0, 1, EUMGSequencePlayMode::Forward);

	}
}
