// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UWidgetPlayer : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings|HP", meta = (BindWidget))
	class UProgressBar* hpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings|MP", meta = (BindWidget))
	class UProgressBar* mpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings|HP", meta = (BindWidget))
		class UTextBlock* Score;

	int32 currentScore = 0;

	void PrintState(float current, float max, bool hp);
	void AddScore(int32 point);



};
