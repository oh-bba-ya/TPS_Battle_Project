// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetClear.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UWidgetClear::NativeConstruct()
{
	// OnColicked�� Delegate�̱� ������ AddDynamic�� �ؾ��Ѵ�.
	// Delegate�̹Ƿ� �ݵ�� ReSume�� UFUNCTION ��ũ�� �߰��ؾ��Ѵ�.
	Btn_Quit2->OnClicked.AddDynamic(this, &UWidgetClear::QuitGame);
	Btn_ReStart2->OnClicked.AddDynamic(this, &UWidgetClear::ReStart);
}


void UWidgetClear::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit"));
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	if (player) {
		UKismetSystemLibrary::QuitGame(GetWorld(), player, EQuitPreference::Quit, true);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Null Player in WidgetGame"));
	}


}

void UWidgetClear::ReStart()
{
	UE_LOG(LogTemp, Warning, TEXT("ReStart"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("SC_Test_M"));

	this->RemoveFromParent();

}