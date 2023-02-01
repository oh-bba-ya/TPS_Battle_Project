// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetGame.h"

void ABattleGameModeBase::ShowMenu()
{
	menu_UI = CreateWidget<UWidgetGame>(GetWorld(), menuWidget);


	if (menu_UI != nullptr) {
		menu_UI->AddToViewport();
	}

	// ���콺 Ŀ�� ��Ÿ����
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}