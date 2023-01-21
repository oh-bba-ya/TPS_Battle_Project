// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildRifle.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TimerManager.h"


AWeaponChildRifle::AWeaponChildRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AWeaponChildRifle::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponName(EWeaponName::EWN_Rifle);

}

/// <summary>
/// LineTrace를 이용한 공격
/// CameraComponent 방향으로 공격한다 (추후 Crosshair (Viewport)방향으로 바꿔야함)
/// </summary>
void AWeaponChildRifle::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	UE_LOG(LogTemp, Warning, TEXT("Rifle Fire"));

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

void AWeaponChildRifle::AutoFire()
{
	GetWorldTimerManager().SetTimer(
		fireTimerHandle,
		this,
		ResetTimer,
		fireInterval
	);
}

void AWeaponChildRifle::ResetTimer()
{

}


