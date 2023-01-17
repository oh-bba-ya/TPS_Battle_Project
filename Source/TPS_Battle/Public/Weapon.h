// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	EWS_Initial UMETA(DisPlayNmae = "Initial State"),
	EWS_PickUp UMETA(DisPlayNmae = "Pickup"),
	EWS_EquipInterpint UMETA(DisPlayNmae = "EquipInterpint"),
	EWS_PickUpped UMETA(DisPlayNmae = "Pickupped"),
	EWS_Equipped UMETA(DisPlayNmae = "Equipped"),
	EWS_Dropped UMETA(DisPlayNmae = "Dropped"),

	EWS_MAX UMETA(DisPlayNmae = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EWeaponName : uint8 {
	EWN_Base UMETA(DisPlayNmae = "Base"),
	EWN_Pistol UMETA(DisPlayNmae = "Pistol"),
	EWN_SubMachineGun UMETA(DisPlayNmae = "SubMachineGun"),
	EWN_ShotGun UMETA(DisPlayNmae = "ShotGun"),
	EWN_SniperGun UMETA(DisPlayNmae = "SniperGun"),
	EWN_RocketGun UMETA(DisPlayNmae = "RocketGun"),
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

	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	UPROPERTY(EditAnywhere , Category = WeaponProperties)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = WeaponProperties)
	class USphereComponent* AreaSphere;


	UPROPERTY(EditAnywhere, Category = WeaponProperties)
		class UWidgetComponent* PickupWidget;

	UPROPERTY(EditAnywhere, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		EWeaponName WeaponName;

	UPROPERTY(EditAnywhere, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		float damage = 1;



public:
	//UPROPERTY(EditAnywhere, Category = WeaponProperties)
		//TSubclassOf<class AProjectile> BulletFactory;


	UFUNCTION()
		void SetVisibilityWIdget(bool overlap);

	FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }
	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

	FORCEINLINE EWeaponName GetWeaponName() const { return WeaponName; }
	FORCEINLINE void SetWeaponName(EWeaponName Name) { WeaponName = Name; }

	//Damage getset ¸¸µé±â

	UFUNCTION()
		virtual void Fire();
};
