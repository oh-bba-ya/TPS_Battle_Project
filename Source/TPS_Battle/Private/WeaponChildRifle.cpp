// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildRifle.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "NiagaraFunctionLibrary.h"


AWeaponChildRifle::AWeaponChildRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetWeaponName(EWeaponName::EWN_Rifle);
}

void AWeaponChildRifle::BeginPlay()
{
	Super::BeginPlay();


}

/// <summary>
/// LineTrace�� �̿��� ����
/// CameraComponent �������� �����Ѵ� (���� Crosshair (Viewport)�������� �ٲ����)
/// </summary>
void AWeaponChildRifle::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Rifle Fire"));
	const USkeletalMeshSocket* firePosition = GetWeaponMesh()->GetSocketByName(FName("FirePosition"));

	if (firePosition != nullptr) {
		const FVector startPos = firePosition->GetSocketLocation(GetWeaponMesh());
		
		if (player != nullptr) {
			FVector endPos = player->GetCamComponent()->GetComponentLocation() 
				+ player->GetCamComponent()->GetForwardVector() 
				* ShotRange;
			FHitResult hitInfo;
			FCollisionQueryParams param;
			param.AddIgnoredActor(this);

			bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, param);
			UE_LOG(LogTemp, Warning, TEXT("hit Name"));
			if (bHit) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), temp, hitInfo.ImpactPoint);
				if (muzzleFlash != nullptr) {
					//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), muzzleFlash, firePosition);
				}
				
			}

		}

		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("fir Fire"));
	}

}


