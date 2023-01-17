// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponChildPistol.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API AWeaponChildPistol : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponChildPistol();


protected:
	virtual void BeginPlay() override;
	

	void Fire() override;

	
	 
public:
	class ABaseCharacter* player;


};
