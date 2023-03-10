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
#include "BattleGameModeBase.h"
#include "Shield.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;


	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	springComp->SetupAttachment(RootComponent);
	springComp->SetRelativeLocation(FVector(0, 70, 90));
	springComp->TargetArmLength = 300;

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

	niagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));

	niagaraComp->SetupAttachment(RootComponent);

	niagaraComp->SetRelativeScale3D(FVector(3, 3, 3));

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	sphereComp->SetupAttachment(niagaraComp);

	sphereComp->SetSphereRadius(50);


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

	anim = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	EquipWeapon(SpawnDefaultWeapon());

	anim->isDead = false;

}



// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (anim->isDead) {
		return;
	}

	SetDirectionMovement(DeltaTime);

	RemoveSkill();



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
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ABaseCharacter::InputAttackRelease);
	
	PlayerInputComponent->BindAction(TEXT("Skill"), IE_Pressed, this, &ABaseCharacter::InputSkill);
	PlayerInputComponent->BindAction(TEXT("Skill"), IE_Released, this, &ABaseCharacter::InputSkillRelease);
	
	
	PlayerInputComponent->BindAction(TEXT("SwapWeapon"), IE_Pressed, this, &ABaseCharacter::InputSwapWeapon);
	
	PlayerInputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &ABaseCharacter::InputPause);


	/*
	* Enhanced Input
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Horizaontal);
	enhancedInputComponent->BindAction(ia_BaseHorizontal, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Horizaontal);

	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Triggered, this, &ABaseCharacter::Base_Vertical);
	enhancedInputComponent->BindAction(ia_BaseVertical, ETriggerEvent::Completed, this, &ABaseCharacter::Base_Vertical);
	*/


}

void ABaseCharacter::OnCameraShake()
{
	if (camShake != NULL) {
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(camShake, 1.0f);
	}
}



void ABaseCharacter::OnHitEvent(float value)
{
	if (basePlayerHP > 0 && !bActiveShield) {
		basePlayerHP -= value;
		if (widgetPlayer != nullptr) {
			widgetPlayer->PrintState(basePlayerHP, 100, true);
		}
		if (basePlayerHP <= 0) {
			Dead();
		}
	}
	else if (basePlayerHP > 0 && bActiveShield) {
		basePlayerMP -= value;
		if (widgetPlayer != nullptr) {
			widgetPlayer->PrintState(GetPlayerMP(), 100, false);
		}
	}
	else if(basePlayerHP <=0) {
		Dead();
	}
}

void ABaseCharacter::Dead()
{
	anim->isDead = true;
	ABattleGameModeBase* gm = Cast<ABattleGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr) {
		gm->ShowMenu();
	}
	
}

void ABaseCharacter::RemoveSkill()
{
	if (niagaraComp->IsActive() && GetPlayerMP() <= 0) {
		niagaraComp->DeactivateImmediate();
		bActiveShield = false;
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
	if (!anim->isDead) {
		Jump();
	}
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
	GetWorld()->GetTimerManager().SetTimer(attackTimer, this, &ABaseCharacter::Attack, attackDelay, true);
	if (!anim->isDead) {
		Attack();
	}
}

void ABaseCharacter::InputAttackRelease()
{
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
}

void ABaseCharacter::Attack()
{
	if (EquippedWeapon != nullptr && EquippedWeapon->GetWeaponState() == EWeaponState::EWS_Equipped) {

		attackDelay = EquippedWeapon->GetFireDelay();

		EquippedWeapon->Fire(EquippedWeapon->hitTarget);
		if (anim != nullptr) {
			if (EquippedWeapon->GetWeaponName() != EWeaponName::EWN_Pistol) {
				anim->PlayAttackRifleAnim();
				anim->isPistol = false;
			}
			else {
				anim->PlayAttackAnim();
				anim->isPistol = true;
			}
		}
	}

	float temp = GetWorld()->GetTimerManager().GetTimerRemaining(attackTimer);
}



void ABaseCharacter::InputSwapWeapon()
{

	WeaponNumber = WeaponNumber % GetMaxCountweapon();
	if (!wArray.IsEmpty() && !anim->isDead) {
		if (wArray.IsValidIndex(WeaponNumber) && wArray[WeaponNumber] != nullptr) {
			EWeaponState curState = wArray[WeaponNumber]->GetWeaponState();
			if (curState == EWeaponState::EWS_PickUpped) {
				UE_LOG(LogTemp, Warning, TEXT("Change"));
				ChangeWeapon(EquippedWeapon);
				EquipWeapon(wArray[WeaponNumber]);
			}
		}
	}
	WeaponNumber += 1;

}

void ABaseCharacter::InputPause()
{

	ABattleGameModeBase* gm = Cast<ABattleGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr) {
		gm->ShowPause();
		gm->isPause = !gm->isPause;
	}
}

void ABaseCharacter::InputSkill()
{
	if (!niagaraComp->IsActive() && GetPlayerMP()>0 && !anim->isDead) {
		niagaraComp->ActivateSystem();
		bActiveShield = true;
	}
	
}

void ABaseCharacter::InputSkillRelease()
{
	if (niagaraComp->IsActive()) {
		niagaraComp->DeactivateImmediate();
		bActiveShield = false;
	}
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
		
		if (EquippedWeapon->GetWeaponName() == EWeaponName::EWN_Pistol) {
			anim->isPistol = true;
			UE_LOG(LogTemp, Warning, TEXT("Pistol"));
		}
		else {
			anim->isPistol = false;
			UE_LOG(LogTemp, Warning, TEXT("Rifle"));
		}
		
	}
}

void ABaseCharacter::PickupWeapon(AWeapon* WeaponToPickup)
{
	if (WeaponToPickup != nullptr) {
		
		if (AddWeaponList(WeaponToPickup)) {
			ChangeWeapon(WeaponToPickup);
		}
		
	}
}

void ABaseCharacter::ChangeWeapon(AWeapon* Weapon)
{
	if (Weapon != nullptr) {

		Weapon->GetAreaSphere()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		const USkeletalMeshSocket* bagSocket = GetMesh()->GetSocketByName(FName("SpineBagSocket"));

		if (bagSocket) {
			bagSocket->AttachActor(Weapon, GetMesh());
		}
		PickuppedWeapon = Weapon;
		PickuppedWeapon->SetWeaponState(EWeaponState::EWS_PickUpped);

	}
}

bool ABaseCharacter::AddWeaponList(AWeapon* Weapon)
{
	if (!wArray.IsEmpty()) {
		bool existed = false;
		for (int32 i = 0; i < wArray.Num(); i++) {
			EWeaponName name = wArray[i]->GetWeaponName();
			if (name == Weapon->GetWeaponName()) {
				existed = true;
				break;
			}
		}

		if (!existed) {
			wArray.Add(Weapon);
			return true;
		}
	}
	else {
		wArray.Add(Weapon);
		return true;
	}

	return false;

}





