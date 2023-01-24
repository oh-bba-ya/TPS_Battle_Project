// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponChildGrenadeGun.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API AWeaponChildGrenadeGun : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeaponChildGrenadeGun();
protected:
	virtual void BeginPlay() override;

	void Fire(const FVector& HitTarget) override;
};
