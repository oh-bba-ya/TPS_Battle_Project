// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetPause.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UWidgetPause : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* Btn_Resume;

	UFUNCTION()
		void Resume();


	
};
