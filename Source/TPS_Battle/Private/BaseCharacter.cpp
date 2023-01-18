// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WidgetPlayer.h"
#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "..\Public\BaseCharacter.h"
#include "BaseCharacterAnimInstance.h"


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
			widgetPlayer->PrintState(basePlayerMP, 100, false);
		}
	}
	EquipWeapon(SpawnDefaultWeapon());

	anim = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	
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

	PlayerInputComponent->BindAction(TEXT("Pickup"), IE_Pressed, this, &ABaseCharacter::InputPickUp);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ABaseCharacter::InputAttack);
	
	PlayerInputComponent->BindAction(TEXT("SwapWeapon"), IE_Pressed, this, &ABaseCharacter::InputSwapWeapon);


	/*
	* Enhanced Input
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Horizaontal);
	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Horizaontal);

	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Vertical);
	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Vertical);
	*/


}



void ABaseCharacter::OnHitEvent(float value)
{
	if (basePlayerHP > 0) {
		basePlayerHP -= value;
		if (widgetPlayer != nullptr) {
			widgetPlayer->PrintState(basePlayerHP, 100, true);
		}
		if (basePlayerHP <= 0) {
			UE_LOG(LogTemp, Warning, TEXT("Player Die"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Die"));
	}
}

#pragma region EnhancedInput 
/* Enhanced Input
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
*/
#pragma endregion

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
	if (OverlapWeapon != nullptr) {
		PickupWeapon(OverlapWeapon);
		OverlapWeapon = nullptr;
	}
}

void ABaseCharacter::InputAttack()
{
	if (EquippedWeapon != nullptr && EquippedWeapon->GetWeaponState() == EWeaponState::EWS_Equipped) {
		EquippedWeapon->Fire();
		if (anim != nullptr) {
			anim->PlayAttackAnim();
		}
	}
}

void ABaseCharacter::InputSwapWeapon()
{
	/*
	* 문제점 : PickupWeapon 함수에서 배열에 추가하는데 계속 배열이 커짐 이거 수정해야할듯
	* 
	*/

	WeaponNumber = WeaponNumber % GetMaxCountweapon();
	int32 size = wArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("wArray size : %d"), size);
	if (!wArray.IsEmpty()) {
		if (wArray[WeaponNumber] != nullptr) {
			EWeaponState curState = wArray[WeaponNumber]->GetWeaponState();
			if (curState == EWeaponState::EWS_PickUpped) {
				PickupWeapon(EquippedWeapon);
				EquipWeapon(wArray[WeaponNumber]);
				UE_LOG(LogTemp, Warning, TEXT("Swap Weapon "));
			}
		}
	}
	WeaponNumber += 1;

	UE_LOG(LogTemp, Warning, TEXT("Weapon number : %d"), WeaponNumber);
}

void ABaseCharacter::SetDirectionMovement(float deltaTime)
{
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

AWeapon* ABaseCharacter::SpawnDefaultWeapon()
{
	if (DefaultWeaponClass != NULL) {
		return GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
	}

	return nullptr;
}

void ABaseCharacter::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip != nullptr) {

		WeaponToEquip->GetAreaSphere()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (HandSocket != nullptr) {
			HandSocket->AttachActor(WeaponToEquip, GetMesh());
		}
		
		EquippedWeapon = WeaponToEquip;
		EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	}
}

void ABaseCharacter::PickupWeapon(AWeapon* WeaponToPickup)
{
	if (WeaponToPickup != nullptr) {
		WeaponToPickup->GetAreaSphere()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		const USkeletalMeshSocket* bagSocket = GetMesh()->GetSocketByName(FName("SpineBagSocket"));

		if (bagSocket) {
			bagSocket->AttachActor(WeaponToPickup, GetMesh());
		}
		PickuppedWeapon = WeaponToPickup;
		PickuppedWeapon->SetWeaponState(EWeaponState::EWS_PickUpped);
		wArray.Add(PickuppedWeapon);
		//AddWeaponList(PickuppedWeapon);
	}
}

void ABaseCharacter::AddWeaponList(AWeapon* Weapon)
{
	if (wArray.Contains(Weapon)) {
		UE_LOG(LogTemp, Warning, TEXT("exist"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Not exist"));
		wArray.Add(Weapon);
	}

}




