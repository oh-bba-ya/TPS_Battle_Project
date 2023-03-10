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
	EWN_Rifle UMETA(DisPlayNmae = "Rifle"),
	EWN_ShotGun UMETA(DisPlayNmae = "ShotGun"),
	EWN_GrenadeGun UMETA(DisPlayNmae = "GrenadeGun"),
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

	UPROPERTY(EditAnywhere, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		float TraceLength = 80000;

	UPROPERTY(EditAnywhere, Category = WeaponProperties)
		class USkeletalMeshComponent* WeaponMesh;



public:
	UPROPERTY(EditDefaultsOnly, Category = WeaponProperties)
		float fireDelay = 1;

	UPROPERTY(EditDefaultsOnly, Category = WeaponProperties)
		class UAnimationAsset* FireAnimation;


	UPROPERTY(EditAnywhere, Category = WeaponProperties)
		TSubclassOf<class AProjectile> bulletFactory;

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);


	UFUNCTION()
		void SetVisibilityWIdget(bool overlap);

	FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }
	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

	FORCEINLINE EWeaponName GetWeaponName() const { return WeaponName; }
	FORCEINLINE void SetWeaponName(EWeaponName Name) { WeaponName = Name; }

	//Damage getset ??????
	FORCEINLINE float GetDamage() const { return damage; }
	FORCEINLINE void SetDamage(float d) { damage = d > 0 ? d : 1; }
	FORCEINLINE  USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	FORCEINLINE float GetTraceLength() const {return TraceLength;}
	FORCEINLINE void SetTraceLength(float L)  { TraceLength = L > 0 ? L : 0 ; }

	FVector hitTarget;

	UFUNCTION()
		virtual void Fire(const FVector& HitTarget);

	class ABaseCharacter* player;

	FORCEINLINE ABaseCharacter* GetBaseCharacter() const { return player; }

	UPROPERTY(EditAnywhere, Category = WeaponProperty)
		class UParticleSystem* BeamParticles;

	FORCEINLINE float GetFireDelay() const { return fireDelay; }
	FORCEINLINE void SetFireDelay(float fd) { fireDelay = fd > 0 ? fd : 1; }
};
