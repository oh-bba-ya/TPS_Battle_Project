// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetGame.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UWidgetGame::NativeConstruct()
{
	// OnColicked도 Delegate이기 때문에 AddDynamic을 해야한다.
	// Delegate이므로 반드시 ReSume에 UFUNCTION 매크로 추가해야한다.
	Btn_Quit->OnClicked.AddDynamic(this, &UWidgetGame::QuitGame);
	Btn_ReStart->OnClicked.AddDynamic(this, &UWidgetGame::ReStart);
}


void UWidgetGame::QuitGame()
{
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	if (player) {
		UKismetSystemLibrary::QuitGame(GetWorld(), player, EQuitPreference::Quit, true);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Null Player in WidgetGame"));
	}


}

void UWidgetGame::ReStart()
{

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("SC_Test_M"));

	this->RemoveFromParent();

}
