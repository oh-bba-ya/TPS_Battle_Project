// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API ABattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = GameModeSettings)
		TSubclassOf<class UWidgetGame> menuWidget;

	UPROPERTY(EditAnywhere, Category = GameModeSettings)
		TSubclassOf<class UWidgetClear> clearWidget;

	class UWidgetGame* menu_UI;

	class UWidgetClear* clear_UI;

	void ShowMenu(bool isClear = false);

	void ShowClear();

	UPROPERTY(EditAnywhere, Category = GameModeSettings)
		TSubclassOf<class UWidgetPause> pauseWidget;

	class UWidgetPause* pause_UI;

	bool isPause = false;

	void ShowPause();




};
