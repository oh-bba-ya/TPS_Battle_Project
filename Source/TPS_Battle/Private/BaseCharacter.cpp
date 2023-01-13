// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "..\Public\BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	springComp->SetupAttachment(RootComponent);
	springComp->SetRelativeLocation(FVector(0, 70, 90));
	springComp->TargetArmLength = 400;

	springComp->bUsePawnControlRotation = true;


	baseCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamComp"));
	baseCamComp->SetupAttachment(springComp);
	baseCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

	APlayerController* playerCon = Cast<APlayerController>(GetController());

	if (playerCon != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
		
		if (subsys != nullptr) {
			subsys->AddMappingContext(imc_BaseMapping, 0);
		}
	}

}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(TEXT("Turn"), this ,&ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this ,&ABaseCharacter::LookUp);

	/*
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Horizaontal);
	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Horizaontal);

	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Vertical);
	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Vertical);
	*/


}

void ABaseCharacter::Base_Horizaontal(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Input"));
	direction.Y = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), direction.Y);

}

void ABaseCharacter::Base_Vertical(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Input"));
	direction.X = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), direction.X);
}

void ABaseCharacter::Base_Jump()
{
}

void ABaseCharacter::Base_Attack()
{
}

void ABaseCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}

void ABaseCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}




