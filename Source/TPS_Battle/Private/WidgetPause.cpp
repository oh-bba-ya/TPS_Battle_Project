// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPause.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

void UWidgetPause::NativeConstruct()
{
	// OnColicked도 Delegate이기 때문에 AddDynamic을 해야한다.
	// Delegate이므로 반드시 ReSume에 UFUNCTION 매크로 추가해야한다.
	Btn_Resume->OnClicked.AddDynamic(this, &UWidgetPause::Resume);
	
}

void UWidgetPause::Resume() {
	// 시간 다시 흐름
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// 마우스 커서 OFF
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	this->RemoveFromViewport();

}

