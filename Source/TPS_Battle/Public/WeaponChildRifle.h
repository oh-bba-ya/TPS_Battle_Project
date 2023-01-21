// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponChildRifle.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API AWeaponChildRifle : public AWeapon
{
	GENERATED_BODY()
public:
	AWeaponChildRifle();


protected:
	virtual void BeginPlay() override;


	void Fire(const FVector& HitTarget) override;

private:
	UPROPERTY(EditAnywhere, Category = RifleProperty)
		float fireInterval = 0.5f;


	FTimerHandle fireTimerHandle;


	void AutoFire();
	void ResetTimer();

public:



	
	
};
