// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetClear.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UWidgetClear : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* Btn_Quit2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* Btn_ReStart2;

	UFUNCTION()
		void QuitGame();

	UFUNCTION()
		void ReStart();
	
};
