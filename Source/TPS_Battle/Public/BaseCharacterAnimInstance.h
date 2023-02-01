// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// Player Move Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float speed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isInAir = false;

	// �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		class UAnimMontage* attackPistolAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		class UAnimMontage* attackRifleAnimMontage;

	void PlayAttackAnim();

	void PlayAttackRifleAnim();

	// �÷��̾� �¿� �̵��ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float direction = 0;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isPistol = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerAnim)
		bool isDead = false;

};
