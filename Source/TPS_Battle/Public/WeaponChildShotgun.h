// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponChildShotgun.generated.h"

/**
 * 
 */
UCLASS()
class TPS_BATTLE_API AWeaponChildShotgun : public AWeapon
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void Fire(const FVector& HitTarget) override;

private:
	UPROPERTY(EditAnywhere, Category = ShotgunProperty)
	int32 NumberOfPellets = 10;

	FVector TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget);

	UPROPERTY(EditAnywhere, Category = WeaponScatter)
		float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere, Category = WeaponScatter)
		float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = WeaponScatter)
		bool bUseScatter = false;
};
