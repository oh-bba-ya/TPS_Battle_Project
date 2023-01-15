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

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		AWeapon* OverlapWeapon;


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

#pragma region Input
	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputJump();
	void InputEnableSprint();
	void InputDisableSprint();
	void InputPickUp();
#pragma endregion

	void SetDirectionMovement(float deltaTime);

	class UWidgetPlayer* widgetPlayer;

	class AWeapon* SpawnDefaultWeapon();

	void EquipWeapon(AWeapon* WeaponToEquip);




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USpringArmComponent* springComp;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCameraComponent* baseCamComp;

	
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<AWeapon> DefaultWeaponClass;


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
	FORCEINLINE void SetPlayerHP(float value) { basePlayerHP = value; }
	FORCEINLINE float GetPlayerMP() const{ return basePlayerMP; }
	FORCEINLINE void SetPlayerMP(float value) { basePlayerMP = value; }
	FORCEINLINE AWeapon* GetOverlapWeapon() const { return OverlapWeapon; }
	FORCEINLINE void SetOverlapWeapon(AWeapon* weapon) { OverlapWeapon = weapon; }

	
	void OnHitEvent(float value);

	



};
