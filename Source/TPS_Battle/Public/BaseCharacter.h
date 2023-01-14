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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USpringArmComponent* springComp;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCameraComponent* baseCamComp;



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


	float GetPlayerHP();
	void SetPlayerHP(float value);

	float GetPlayerMP();
	void SetPlayerMP(float value);
	
	void OnHitEvent(float value);


private:
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float basePlayerHP = 100;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float basePlayerMP = 100;



#pragma region Enhanced Input
	// Enhanced Input
	void Base_Horizaontal(const FInputActionValue& value);
	void Base_Vertical(const FInputActionValue& value);
	void Base_Jump();
	void Base_Attack();
#pragma endregion


	void Turn(float value);
	void LookUp(float value);


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		float walkSpeed = 600;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		float sprintSpeed = 1000;


	FVector direction;

	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputJump();
	void InputEnableSprint();
	void InputDisableSprint();
	void InputPickUp();





	void SetDirectionMovement(float deltaTime);

	class UWidgetPlayer* widgetPlayer;





};
