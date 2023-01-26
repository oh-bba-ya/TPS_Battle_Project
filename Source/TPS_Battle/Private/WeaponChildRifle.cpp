// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildRifle.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


AWeaponChildRifle::AWeaponChildRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AWeaponChildRifle::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponName(EWeaponName::EWN_Rifle);

	SetFireDelay(0.2f);

}


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






