// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetGame.h"
#include "WidgetPause.h"
#include "WidgetClear.h"

void ABattleGameModeBase::ShowMenu(bool isClear)
{
	if (!isClear) {
		menu_UI = CreateWidget<UWidgetGame>(GetWorld(), menuWidget);
		if (menu_UI != nullptr) {
			menu_UI->AddToViewport();
		}
	}
	
	// 마우스 커서 나타내기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}

void ABattleGameModeBase::ShowClear()
{
	clear_UI = CreateWidget<UWidgetClear>(GetWorld(), clearWidget);
	if (clear_UI != nullptr) {
		clear_UI->AddToViewport();
	}

	// 마우스 커서 나타내기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}

void ABattleGameModeBase::ShowPause()
{
	pause_UI = CreateWidget<UWidgetPause>(GetWorld(), pauseWidget);

	if (pause_UI != nullptr && !isPause) {
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		pause_UI->AddToViewport();
	}

	// 마우스 커서 나타내기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
