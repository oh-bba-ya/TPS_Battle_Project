// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WidgetPlayer.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;


	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	springComp->SetupAttachment(RootComponent);
	springComp->SetRelativeLocation(FVector(0, 70, 90));
	springComp->TargetArmLength = 400;

	springComp->bUsePawnControlRotation = true;


	baseCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamComp"));
	baseCamComp->SetupAttachment(springComp);
	baseCamComp->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	

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

	if (BP_WidgetPlayer != nullptr) {
		widgetPlayer = CreateWidget<UWidgetPlayer>(GetWorld(), BP_WidgetPlayer);
		if (widgetPlayer != nullptr) {
			widgetPlayer->AddToViewport();
			widgetPlayer->PrintState(basePlayerHP, 100, true);
		}
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetDirectionMovement(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(TEXT("Turn"), this ,&ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this ,&ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ABaseCharacter::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ABaseCharacter::InputVertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacter::InputJump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ABaseCharacter::InputEnableSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ABaseCharacter::InputDisableSprint);


	/*
	* Enhanced Input
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Horizaontal);
	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Horizaontal);

	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Vertical);
	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Vertical);
	*/


}

float ABaseCharacter::GetPlayerHP()
{
	return basePlayerHP;
}

void ABaseCharacter::SetPlayerHP(float value)
{
	basePlayerHP = value;
}

float ABaseCharacter::GetPlayerMP()
{
	return basePlayerMP;
}

void ABaseCharacter::SetPlayerMP(float value)
{
	basePlayerMP = value;
}

void ABaseCharacter::OnHitEvent(float value)
{
	if (basePlayerHP > 0) {
		basePlayerHP -= value;
		if (widgetPlayer != nullptr) {
			widgetPlayer->PrintState(basePlayerHP, 100, true);
		}
		if (basePlayerHP <= 0) {
			Destroy();
		}
	}
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

void ABaseCharacter::InputHorizontal(float value)
{
	direction.Y = value;
}

void ABaseCharacter::InputVertical(float value)
{
	direction.X = value;
}

void ABaseCharacter::InputJump()
{
	Jump();
}

void ABaseCharacter::InputEnableSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;

}
void ABaseCharacter::InputDisableSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ABaseCharacter::InputPickUp()
{

}

void ABaseCharacter::SetDirectionMovement(float deltaTime)
{
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}




