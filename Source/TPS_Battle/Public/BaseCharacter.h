// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TPS_BATTLE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float basePlayerHP = 100;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float basePlayerMP = 100;

	UPROPERTY(EditAnywhere, Category = PlayerWeaponSettings)
		class AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, Category = PlayerWeaponSettings)
		AWeapon* OverlapWeapon;

	UPROPERTY(EditAnywhere, Category = PlayerWeaponSettings)
		class AWeapon* PickuppedWeapon;

	UPROPERTY(EditAnywhere, Category = PlayerWeaponSettings)
		TArray<AWeapon*> wArray;

	class UBaseCharacterAnimInstance* anim;

#pragma region Enhanced Input
	/*
	// Enhanced Input
	void Base_Horizaontal(const FInputActionValue& value);
	void Base_Vertical(const FInputActionValue& value);
	void Base_Jump();
	void Base_Attack();
	*/
#pragma endregion


	void Turn(float value);
	void LookUp(float value);


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		float walkSpeed = 600;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		float sprintSpeed = 1000;


	FVector direction;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UNiagaraComponent* niagaraComp;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USphereComponent* sphereComp;

	bool bActiveShield = false;

#pragma region Input
	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputJump();
	void InputEnableSprint();
	void InputDisableSprint();
	void InputPickUp();
	void InputAttack();
	void InputAttackRelease();
	void Attack();
	void InputSwapWeapon();

	int32 WeaponNumber = 0;

	UPROPERTY(EditAnywhere, Category = PlayerWeaponSettings)
	int32 MaxCountWeapon = 5;

	FTimerHandle attackTimer;

	float attackDelay = 1;

	void InputSkill();
	void InputSkillRelease();

#pragma endregion

	void SetDirectionMovement(float deltaTime);


	class AWeapon* SpawnDefaultWeapon();

	void EquipWeapon(AWeapon* WeaponToEquip);

	void PickupWeapon(AWeapon* WeaponToPickup);

	void ChangeWeapon(AWeapon* Weapon);

	bool AddWeaponList(AWeapon* WeaponToPickup);




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	class UWidgetPlayer* widgetPlayer;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USpringArmComponent* springComp;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCameraComponent* baseCamComp;

	
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UCameraShakeBase> camShake;

	void OnCameraShake();

#pragma region Enhanced Input
	// Enhanced Input
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UInputAction* ia_BaseHorizontal;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UInputAction* ia_BaseVertical;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UInputAction* ia_BaseAttack;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UInputAction* ia_BaseJump;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputMappingContext* imc_BaseMapping;
#pragma endregion


	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UWidgetPlayer> BP_WidgetPlayer;


	FORCEINLINE float GetPlayerHP() const {return basePlayerHP; }
	FORCEINLINE void SetPlayerHP(float value) { basePlayerHP = (value > 0 ? value : 0); }
	FORCEINLINE float GetPlayerMP() const{ return basePlayerMP; }
	FORCEINLINE void SetPlayerMP(float value) { basePlayerMP = (value > 0 ? value : 0); }
	FORCEINLINE AWeapon* GetOverlapWeapon() const { return OverlapWeapon; }
	FORCEINLINE void SetOverlapWeapon(AWeapon* weapon) { OverlapWeapon = weapon; }
	FORCEINLINE void SetMaxCountWeapon(int32 count) { MaxCountWeapon = count > 0 ? count : 1; }
	FORCEINLINE int32 GetMaxCountweapon() { return MaxCountWeapon; }
	FORCEINLINE UCameraComponent* GetCamComponent() const { return baseCamComp; }
	void OnHitEvent(float value = 10);

	
	void Dead();


	void RemoveSkill();


};
