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

	class UWidgetGame* menu_UI;

	void ShowMenu();
};
