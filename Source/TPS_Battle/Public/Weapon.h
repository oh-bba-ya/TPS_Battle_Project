// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	EWS_Initial UMETA(DisPlayNmae = "Initial State"),
	EWS_Equipped UMETA(DisPlayNmae = "Equipped"),
	EWS_Dropped UMETA(DisPlayNmae = "Dropped"),

	EWS_MAX UMETA(DisPlayNmae = "DefaultMAX")
};

UCLASS()
class TPS_BATTLE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

private:
	UPROPERTY(EditAnywhere , Category = WeaponProperties)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = WeaponProperties)
	class USphereComponent* AreaSphere;

	UPROPERTY(EditAnyWhere)
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, Category = WeaponProperties)
		class UWidgetComponent* PickupWidget;

};
