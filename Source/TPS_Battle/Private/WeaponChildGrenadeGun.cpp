// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildGrenadeGun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"

AWeaponChildGrenadeGun::AWeaponChildGrenadeGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWeaponChildGrenadeGun::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponName(EWeaponName::EWN_GrenadeGun);

}


void AWeaponChildGrenadeGun::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	UE_LOG(LogTemp, Warning, TEXT("GrenadeGun Fire"));

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));

	if (MuzzleFlashSocket) {
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());

		FVector ToTarget = HitTarget - SocketTransform.GetLocation();

		FRotator TargetRotation = ToTarget.Rotation();

		if (bulletFactory) {
			UWorld* World = GetWorld();
			if (World) {
				World->SpawnActor<AProjectile>(bulletFactory, SocketTransform.GetLocation(), TargetRotation);
			}
		}

	}

}