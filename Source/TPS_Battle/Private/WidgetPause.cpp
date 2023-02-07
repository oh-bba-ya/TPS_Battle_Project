// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPause.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

void UWidgetPause::NativeConstruct()
{
	// OnColicked�� Delegate�̱� ������ AddDynamic�� �ؾ��Ѵ�.
	// Delegate�̹Ƿ� �ݵ�� ReSume�� UFUNCTION ��ũ�� �߰��ؾ��Ѵ�.
	Btn_Resume->OnClicked.AddDynamic(this, &UWidgetPause::Resume);
	
}

void UWidgetPause::Resume() {
	// �ð� �ٽ� �帧
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// ���콺 Ŀ�� OFF
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	this->RemoveFromViewport();

}

