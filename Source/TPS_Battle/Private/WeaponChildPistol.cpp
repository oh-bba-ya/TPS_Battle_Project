// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildPistol.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"

AWeaponChildPistol::AWeaponChildPistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetWeaponName(EWeaponName::EWN_Pistol);
}

void AWeaponChildPistol::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ABaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));
	if (player != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("playerNull"));
	}
	
}

void AWeaponChildPistol::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	UE_LOG(LogTemp, Warning, TEXT("Pistol Fire"));

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));

	if (MuzzleFlashSocket) {
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());

		FVector ToTarget = HitTarget - SocketTransform.GetLocation();

		FRotator TargetRotation = ToTarget.Rotation();

		if (bulletFactory) {
			UWorld* World = GetWorld();
			if (World) {
				World->SpawnActor<AProjectile>(bulletFactory, SocketTransform.GetLocation(),TargetRotation);
			}
		}
	}

}


